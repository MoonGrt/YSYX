package soc.riscv.e

import chisel3._
import soc.riscv.Parameters.Riscv32E._
import soc.riscv.Parameters.AxiPackage
import soc.perip.mem._
import soc.perip.uart._
import soc.perip.clint._
import soc.util._
import bus.amba.axi.common._
import bus.amba.axi.axifull._
import freechips.rocketchip.amba.axi4.{
  AXI4Bundle,
  AXI4BundleParameters => RCAXI4BundleParameters
}

/** The single RISCV32E implementation.
  *
  * The pipeline always uses InstBus/DataBus internally.  `axiPackage` selects
  * only the AXI bundle and adapters exposed at the CPU boundary.
  */
class Riscv32E(
  customParams: AxiParams,
  rocketParams: RCAXI4BundleParameters,
  resetPc: BigInt = 0x80000000L
) extends Module {
  require(customParams.dataBits == DataWidth)
  require(rocketParams.dataBits == DataWidth)

  val io = IO(new Bundle {
    val inst =
      if (memBusType != BusType.AXI) new InstBus(DataWidth)
      else if (axiPackage == AxiPackage.Custom) new AXI4MasterBundle(customParams)
      else new AXI4Bundle(rocketParams)
    val data =
      if (memBusType != BusType.AXI) new DataBus(DataWidth)
      else if (axiPackage == AxiPackage.Custom) new AXI4MasterBundle(customParams)
      else new AXI4Bundle(rocketParams)
  })
  dontTouch(io.inst)
  dontTouch(io.data)

  val ifu = Module(new IFU(resetPc))
  val idu = Module(new IDU)
  val exu = Module(new EXU)
  val lsu = Module(new LSU)
  val wbu = Module(new WBU)

  if (memBusType == BusType.AXI) {
    if (axiPackage == AxiPackage.Custom) {
      val iBridge = Module(new IBusBridge(customParams))
      val dBridge = Module(new DBusBridge(customParams))
      iBridge.ibus <> ifu.io.ibus
      iBridge.axi <> io.inst
      dBridge.dbus <> lsu.io.dbus
      dBridge.axi <> io.data
    } else {
      val iBridge = Module(new RCIBusBridge(rocketParams))
      val dBridge = Module(new RCDBusBridge(rocketParams))
      iBridge.io.ibus <> ifu.io.ibus
      iBridge.io.axi <> io.inst
      dBridge.io.dbus <> lsu.io.dbus
      dBridge.io.axi <> io.data
    }
  } else {
    require(axiPackage == AxiPackage.Custom,
      "direct InstBus/DataBus mode only supports the custom bus implementation")
    io.inst <> ifu.io.ibus
    io.data <> lsu.io.dbus
  }

  exu.io.br <> ifu.io.in
  ifu.io.out <> idu.io.ifuin
  wbu.io.out <> idu.io.wbuin
  idu.io.out <> exu.io.in
  exu.io.out <> lsu.io.in
  lsu.io.out <> wbu.io.in

  // Simulation-only performance events. The counters live in the C++
  // environment, so they do not become part of the synthesized processor.
  val perfEvents = WireInit(0.U(32.W))
  perfEvents :=
    (ifu.io.ibus.req.fire.asUInt       << 0) |
    (ifu.io.ibus.resp.fire.asUInt      << 1) |
    (ifu.io.out.fire.asUInt            << 2) |
    ((ifu.io.ibus.req.valid && !ifu.io.ibus.req.ready).asUInt << 3) |
    ((ifu.io.ibus.resp.ready && !ifu.io.ibus.resp.valid).asUInt << 4) |
    ((ifu.io.out.valid && !ifu.io.out.ready).asUInt << 5) |
    (lsu.io.dbus.req.fire.asUInt       << 6) |
    (lsu.io.dbus.resp.fire.asUInt      << 7) |
    ((lsu.io.dbus.resp.ready && !lsu.io.dbus.resp.valid).asUInt << 8) |
    (exu.io.out.fire.asUInt            << 9) |
    ((lsu.io.dbus.req.fire && lsu.io.dbus.req.bits.ren).asUInt << 10) |
    ((lsu.io.dbus.req.fire && lsu.io.dbus.req.bits.wen).asUInt << 11)

  val perf = Module(new DpiPerfEventBB)
  perf.io.clk    := clock
  perf.io.en     := !reset.asBool
  perf.io.events := perfEvents
}

/** Standalone MEMU top: CPU plus simulation memory and peripherals. */
class Riscv32ETop(resetPc: BigInt = 0x80000000L) extends Module {
  private val masterPort = AXI4MasterPortParameters(
    masters = Seq(AXI4MasterParameters(name = "cpu_master", id = IdRange(0, 4)))
  )
  private val slavePort = AXI4SlavePortParameters(
    slaves = Seq(
      AXI4SlaveParameters(
        address = Seq(AddressSet(base = 0x80000000L, mask = 0x07ffffffL)),
        supportsWrite = TransferSizes(0, 4),
        supportsRead = TransferSizes(0, 4)
      ),
      AXI4SlaveParameters(
        address = Seq(AddressSet(base = 0xa0000000L, mask = 0x00000fffL)),
        supportsWrite = TransferSizes(0, 4),
        supportsRead = TransferSizes(0, 4)
      ),
      AXI4SlaveParameters(
        address = Seq(AddressSet(base = 0xb0000000L, mask = 0x00000fffL)),
        supportsWrite = TransferSizes(0, 4),
        supportsRead = TransferSizes(0, 4)
      )
    ),
    beatBytes = 4
  )
  private implicit val params: AxiParameters =
    new WithAxiPorts(masterPort, slavePort) ++ new BaseAxiConfig
  private val customParams = AxiParams.fromPortParameters
  private val rocketParams = RCAXI4BundleParameters(
    addrBits = customParams.addrBits,
    dataBits = customParams.dataBits,
    idBits = customParams.idBits
  )

  val cpu = Module(new Riscv32E(customParams, rocketParams, resetPc))

  if (memBusType == BusType.AXI) {
    val xbar = Module(new AxiCrossbar(
      p = customParams,
      nMasters = 2,
      slaveAddress = Seq(
        AddressSet(0x80000000L, 0x07ffffffL),
        AddressSet(0xa0000000L, 0x00000fffL),
        AddressSet(0xb0000000L, 0x00000fffL)
      )
    ))
    val sram  = Module(new AXIRAM(customParams, useDpi = memUseDpi, delayCfg = memDelayCfg))
    val uart  = Module(new AXIUART(customParams))
    val clint = Module(new AXICLINT(customParams))

    if (axiPackage == AxiPackage.Custom) {
      xbar.io.fromMasters(0) <> cpu.io.inst
      xbar.io.fromMasters(1) <> cpu.io.data
    } else {
      val instAdapter = Module(new RCToCustomAXI(rocketParams, customParams))
      val dataAdapter = Module(new RCToCustomAXI(rocketParams, customParams))
      instAdapter.io.rc <> cpu.io.inst
      dataAdapter.io.rc <> cpu.io.data
      xbar.io.fromMasters(0) <> instAdapter.io.custom
      xbar.io.fromMasters(1) <> dataAdapter.io.custom
    }

    sram.io <> xbar.io.toSlaves(0)
    uart.io <> xbar.io.toSlaves(1)
    clint.io <> xbar.io.toSlaves(2)
  } else {
    val rom = Module(new ROM(useDpi = memUseDpi, delayCfg = memDelayCfg))
    val ram = Module(new RAM(useDpi = memUseDpi, delayCfg = memDelayCfg))
    rom.io <> cpu.io.inst
    ram.io <> cpu.io.data
  }
}
