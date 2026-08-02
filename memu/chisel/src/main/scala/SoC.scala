package soc

import chisel3._
import chisel3.util._

import freechips.rocketchip.diplomacy._
import org.chipsalliance.cde.config.Parameters
import freechips.rocketchip.subsystem._
import freechips.rocketchip.util._
import freechips.rocketchip.amba.axi4._
import freechips.rocketchip.amba.apb._
import freechips.rocketchip.system.SimAXIMem

import soc.util._
import soc.perip._
import soc.riscv.Parameters.{BootSource, Riscv32E, SoCDevices}

object AXI4SlaveNodeGenerator {
  def apply(params: Option[MasterPortParams], address: Seq[AddressSet])(implicit valName: ValName) =
    AXI4SlaveNode(params.map(p => AXI4SlavePortParameters(
      slaves = Seq(AXI4SlaveParameters(
        address       = address,
        executable    = p.executable,
        supportsWrite = TransferSizes(1, p.maxXferBytes),
        supportsRead  = TransferSizes(1, p.maxXferBytes))),
      beatBytes = p.beatBytes
    )).toSeq)
}

/** Pass-through AXI node that fails fast on requests outside the downstream map. */
class AXI4AddressMonitor(implicit p: Parameters) extends LazyModule {
  val node = AXI4IdentityNode()
  override lazy val module = new Impl
  class Impl extends LazyModuleImp(this) {
    (node.in zip node.out).foreach { case ((in, _), (out, edgeOut)) =>
      out <> in
      val mappedAddresses =
        edgeOut.slave.slaves.flatMap(_.address)
      def isMapped(address: UInt): Bool =
        mappedAddresses.map(_.contains(address)).reduce(_ || _)
      when(in.ar.valid) {
        assert(isMapped(in.ar.bits.addr),
          cf"Illegal AXI read address 0x${in.ar.bits.addr}%x")
      }
      when(in.aw.valid) {
        assert(isMapped(in.aw.bits.addr),
          cf"Illegal AXI write address 0x${in.aw.bits.addr}%x")
      }
    }
  }
}

class SoCASIC(resetPc: BigInt = Riscv32E.bootAddress)(implicit p: Parameters) extends LazyModule {
  val xbar1 = AXI4Xbar()
  val xbar2 = AXI4Xbar()
  val apbxbar = LazyModule(new APBFanout).node
  val core = LazyModule(new CPU(
    idBits = ChipLinkParam.idBits,
    resetPc = resetPc
  ))
  val addressMonitor = LazyModule(new AXI4AddressMonitor)
  val chipMaster = if (Config.hasChipLink) Some(LazyModule(new ChipLinkMaster)) else None
  val chiplinkNode = if (Config.hasChipLink) Some(AXI4SlaveNodeGenerator(p(ExtBus), ChipLinkParam.allSpace)) else None

  val luart = LazyModule(new APBUart16550(AddressSet.misaligned(SoCDevices.uartBase, SoCDevices.uartSize)))
  val lgpio = LazyModule(new APBGPIO(AddressSet.misaligned(SoCDevices.gpioBase, SoCDevices.gpioSize)))
  val lkeyboard = LazyModule(new APBKeyboard(AddressSet.misaligned(SoCDevices.ps2Base, SoCDevices.ps2Size)))
  val lvga = LazyModule(new APBVGA(AddressSet.misaligned(SoCDevices.vgaBase, SoCDevices.vgaSize)))
  val lspi  = LazyModule(new APBSPI(
    AddressSet.misaligned(SoCDevices.spiBase, SoCDevices.spiSize) ++
    AddressSet.misaligned(SoCDevices.flashBase, SoCDevices.flashSize)
  ))
  val lmrom = if (Riscv32E.bootSource == BootSource.MROM)
    Some(LazyModule(new AXI4MROM(AddressSet.misaligned(SoCDevices.mromBase, SoCDevices.mromSize))))
  else None
  val lpsram = LazyModule(new APBPSRAM(AddressSet.misaligned(SoCDevices.psramBase, SoCDevices.psramSize)))
  val sramNode = AXI4RAM(AddressSet.misaligned(SoCDevices.sramBase, SoCDevices.sramSize).head, false, true, 4, None, Nil, false)

  val sdramAddressSet = AddressSet.misaligned(SoCDevices.sdramBase, SoCDevices.sdramSize)
  val lsdram_apb = if (!Config.sdramUseAXI) Some(LazyModule(new APBSDRAM (sdramAddressSet))) else None
  val lsdram_axi = if ( Config.sdramUseAXI) Some(LazyModule(new AXI4SDRAM(sdramAddressSet))) else None

  List(lspi.node, luart.node, lpsram.node, lgpio.node, lkeyboard.node, lvga.node).map(_ := apbxbar)
  apbxbar := APBDelayer() := AXI4ToAPB() := AXI4Buffer() := xbar2
  sramNode := AXI4Buffer() := xbar2
  lmrom.foreach { mrom => mrom.node := AXI4Buffer() := xbar2 }
  xbar2 := AXI4UserYanker(Some(1)) := AXI4Fragmenter() := xbar1
  if (Config.sdramUseAXI) lsdram_axi.get.node := soc.util.AXI4Delayer() := xbar1
  else                    lsdram_apb.get.node := apbxbar
  if (Config.hasChipLink) chiplinkNode.get := xbar1
  xbar1 :=* addressMonitor.node
  addressMonitor.node :=* core.masterNode

  override lazy val module = new Impl
  class Impl extends LazyModuleImp(this) with DontTouch {
    // generate delayed reset for cpu, since chiplink should finish reset
    // to initialize some async modules before accept any requests from cpu
    // cpu.module.reset := SynchronizerShiftReg(reset.asBool, 10) || reset.asBool
    val resetPipe = RegInit("b1111111111".U(10.W))
    when(reset.asBool) {
      resetPipe := "b1111111111".U
    }.otherwise {
      resetPipe := Cat(resetPipe(8, 0), false.B)
    }
    core.module.reset := reset.asBool || resetPipe.orR
    val fpga_io = if (Config.hasChipLink) Some(IO(chiselTypeOf(chipMaster.get.module.fpga_io))) else None
    if (Config.hasChipLink) {
      // connect chiplink slave interface to crossbar
      (chipMaster.get.slave zip chiplinkNode.get.in) foreach { case (io, (bundle, _)) => io <> bundle }
      // connect chiplink dma interface to cpu
      core.module.slave <> chipMaster.get.master_mem(0)
      // expose chiplink fpga I/O interface as ports
      fpga_io.get <> chipMaster.get.module.fpga_io
    } else {
      core.module.slave := DontCare
    }

    // connect interrupt signal to cpu
    val intr_from_chipSlave = IO(Input(Bool()))
    core.module.interrupt := intr_from_chipSlave
    val sdramBundle = if (Config.sdramUseAXI) lsdram_axi.get.module.sdram_bundle
                      else                    lsdram_apb.get.module.sdram_bundle

    // expose slave I/O interface as ports
    val spi = IO(chiselTypeOf(lspi.module.spi_bundle))
    val uart = IO(chiselTypeOf(luart.module.uart))
    val psram = IO(chiselTypeOf(lpsram.module.qspi_bundle))
    val sdram = IO(chiselTypeOf(sdramBundle))
    val gpio = IO(chiselTypeOf(lgpio.module.gpio_bundle))
    val ps2 = IO(chiselTypeOf(lkeyboard.module.ps2_bundle))
    val vga = IO(chiselTypeOf(lvga.module.vga_bundle))
    uart <> luart.module.uart
    spi <> lspi.module.spi_bundle
    psram <> lpsram.module.qspi_bundle
    sdram <> sdramBundle
    gpio <> lgpio.module.gpio_bundle
    ps2 <> lkeyboard.module.ps2_bundle
    vga <> lvga.module.vga_bundle
  }
}

class SoCFPGA(implicit p: Parameters) extends ChipLinkSlave

class SoCTop(implicit p: Parameters) extends LazyModule {
  val asic = LazyModule(new SoCASIC)
  ElaborationArtefacts.add("graphml", graphML)

  override lazy val module = new Impl
  class Impl extends LazyModuleImp(this) with DontTouch {
    val masic = asic.module
    if (Config.hasChipLink) {
      val fpga = LazyModule(new SoCFPGA)
      val mfpga = Module(fpga.module)
      masic.dontTouchPorts()
      masic.fpga_io.get.b2c <> mfpga.fpga_io.c2b
      mfpga.fpga_io.b2c <> masic.fpga_io.get.c2b
      (fpga.master_mem zip fpga.axi4MasterMemNode.in).map { case (io, (_, edge)) =>
        val mem = LazyModule(new SimAXIMem(edge,
          base = ChipLinkParam.mem.base, size = ChipLinkParam.mem.mask + 1))
        Module(mem.module)
        mem.io_axi4.head <> io
      }
      fpga.master_mmio.map(_ := DontCare)
      fpga.slave.map(_ := DontCare)
    }

    masic.intr_from_chipSlave := false.B
    val flash = Module(new flash)
    flash.io <> masic.spi
    flash.io.ss := masic.spi.ss(0)
    val bitrev = Module(new bitrev)
    bitrev.io <> masic.spi
    bitrev.io.ss := masic.spi.ss(7)
    masic.spi.miso := List(bitrev.io, flash.io).map(_.miso).reduce(_&&_)

    val psram = Module(new psram)
    psram.io <> masic.psram
    val sdram = Module(new sdram)
    sdram.io <> masic.sdram

    val externalPins = IO(new Bundle{
      val gpio = chiselTypeOf(masic.gpio)
      val ps2 = chiselTypeOf(masic.ps2)
      val vga = chiselTypeOf(masic.vga)
      val uart = chiselTypeOf(masic.uart)
    })
    externalPins.gpio <> masic.gpio
    externalPins.ps2 <> masic.ps2
    externalPins.vga <> masic.vga
    externalPins.uart <> masic.uart
  }
}



import org.chipsalliance.cde.config.{Parameters, Config}
import freechips.rocketchip.system.{Edge32BitConfig, DefaultRV32Config}

object Config {
  def hasChipLink: Boolean = false
  def sdramUseAXI: Boolean = true
}
