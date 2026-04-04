package riscv.e

import chisel3._
import chisel3.util._
import riscv.Constants._
import riscv.Constants.Riscv32E._
import riscv.util._

// ---------------------------
// Riscv32E CPU
// ---------------------------
class InstBus extends Bundle{
  val addr = Decoupled(UInt(DataWidth.W))
  val data = Flipped(Decoupled(UInt(DataWidth.W)))
}
class DataBus extends Bundle{
  val memRen   = Output(Bool())  // read enable
  val memWen   = Output(Bool())  // write enable
  val memMask  = Output(UInt((DataWidth/8).W))
  val memAddr  = Output(UInt(DataWidth.W))
  val memWdata = Output(UInt(DataWidth.W))
  val memRdata = Input(UInt(DataWidth.W))
}
class Riscv32E extends Module {
  val io = IO(new Bundle {
    val inst = new InstBus
    val data = new DataBus
  })

  // Modules
  val ifu = Module(new IFU)
  val idu = Module(new IDU)
  val exu = Module(new EXU)
  val lsu = Module(new LSU)
  val wbu = Module(new WBU)

  // Inst Bus
  io.inst <> ifu.io.bus
  // Data Bus
  io.data <> lsu.io.bus

  // IFU
  ifu.io.in <> exu.io.br
  // IDU
  idu.io.ifuin <> ifu.io.out
  idu.io.wbuin <> wbu.io.out
  // EXU
  exu.io.in <> idu.io.out
  // LSU
  lsu.io.in <> exu.io.out
  // WBU
  wbu.io.in <> lsu.io.out
}

// ---------------------------
// Riscv32E TOP = CPU + ROM + RAM
// ---------------------------
class Riscv32ETOP extends Module {
  val cpu = Module(new Riscv32E)
  val rom = Module(new ROM_DPI)
  val ram = Module(new RAM_DPI)
  // Inst
  cpu.io.inst.addr.ready := true.B
  rom.io.addr := cpu.io.inst.addr.bits
  cpu.io.inst.data.valid := cpu.io.inst.data.ready
  cpu.io.inst.data.bits := rom.io.data
  // Data
  ram.io.clk   := clock
  ram.io.ren   := cpu.io.data.memRen
  ram.io.wen   := cpu.io.data.memWen
  ram.io.mask  := cpu.io.data.memMask
  ram.io.addr  := cpu.io.data.memAddr
  ram.io.wdata := cpu.io.data.memWdata
  cpu.io.data.memRdata := ram.io.rdata
}
