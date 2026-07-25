package soc

import chisel3._
import chisel3.util._

import org.chipsalliance.cde.config.Parameters
import freechips.rocketchip.subsystem._
import freechips.rocketchip.amba.axi4._
import freechips.rocketchip.diplomacy._
import freechips.rocketchip.util._

import soc.util._
import soc.riscv.e.Riscv32ERocketChip

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

class CPU(idBits: Int)(implicit p: Parameters) extends LazyModule {
  private def master(name: String) = AXI4MasterPortParameters(
    masters = Seq(AXI4MasterParameters(
      name = name,
      id   = IdRange(0, 1 << idBits))))

  val masterNode = AXI4MasterNode(Seq(
    master("riscv32e-ibus"),
    master("riscv32e-dbus")
  ))
  lazy val module = new Impl
  class Impl extends LazyModuleImp(this) {
    val (inst, _) = masterNode.out(0)
    val (data, _) = masterNode.out(1)
    val interrupt = IO(Input(Bool()))
    val slave = IO(Flipped(AXI4Bundle(CPUAXI4BundleParameters())))

    val cpu = Module(new Riscv32ERocketChip(CPUAXI4BundleParameters()))
    cpu.io.inst <> inst
    cpu.io.data <> data
    slave := DontCare
  }
}
