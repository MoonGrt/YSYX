package soc

import chisel3._
import chisel3.util._

import org.chipsalliance.cde.config.Parameters
import freechips.rocketchip.subsystem._
import freechips.rocketchip.amba.axi4._
import freechips.rocketchip.diplomacy._
import freechips.rocketchip.util._

import soc.util._
import soc.riscv.e.Riscv32E
import soc.riscv.Parameters.{AxiPackage, Riscv32E => Riscv32EParameters}
import bus.amba.axi.common.AxiParams

object CPUAXI4BundleParameters {
  def apply() = AXI4BundleParameters(addrBits = 32, dataBits = 32, idBits = ChipLinkParam.idBits)
}

class ysyx_00000000 extends BlackBox {
  val io = IO(new Bundle {
    val clock = Input(Clock())
    val reset = Input(Reset())
    val io_interrupt = Input(Bool())
    val io_master = AXI4Bundle(CPUAXI4BundleParameters())
    val io_slave = Flipped(AXI4Bundle(CPUAXI4BundleParameters()))
  })
}

class CPU(
  idBits: Int,
  resetPc: BigInt = 0x80000000L
)(implicit p: Parameters) extends LazyModule {
  require(idBits >= 2, "the merged CPU AXI port needs one source-ID bit")

  private def master(name: String) = AXI4MasterPortParameters(
    masters = Seq(AXI4MasterParameters(
      name = name,
      id   = IdRange(0, 1 << idBits))
    )
  )

  val masterNode = AXI4MasterNode(Seq(master("riscv32e")))
  lazy val module = new Impl
  class Impl extends LazyModuleImp(this) {
    val (master, _) = masterNode.out(0)
    val interrupt = IO(Input(Bool()))
    val slave = IO(Flipped(AXI4Bundle(CPUAXI4BundleParameters())))

    private val rocketParams = AXI4BundleParameters(
      addrBits = master.params.addrBits,
      dataBits = master.params.dataBits,
      idBits = idBits - 1
    )
    private val customParams = AxiParams(
      addrBits = rocketParams.addrBits,
      dataBits = rocketParams.dataBits,
      idBits = rocketParams.idBits
    )
    val cpu = Module(new Riscv32E(
      customParams,
      rocketParams,
      resetPc = resetPc
    ))
    val merger = Module(new AXI4NonBlockingMerger(rocketParams, master.params))
    if (Riscv32EParameters.axiPackage == AxiPackage.RocketChip) {
      merger.io.inst <> cpu.io.inst
      merger.io.data <> cpu.io.data
    } else {
      val instAdapter = Module(new CustomToRCAXI(customParams, rocketParams))
      val dataAdapter = Module(new CustomToRCAXI(customParams, rocketParams))
      instAdapter.io.custom <> cpu.io.inst
      dataAdapter.io.custom <> cpu.io.data
      merger.io.inst <> instAdapter.io.rc
      merger.io.data <> dataAdapter.io.rc
    }
    master <> merger.io.out
    slave := DontCare
  }
}
