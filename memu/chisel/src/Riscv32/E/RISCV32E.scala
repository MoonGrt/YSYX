package riscv.e

import chisel3._
import chisel3.util._
import riscv.Constants._
import riscv.Constants.Riscv32E._
import riscv.util._

// ---------------------------
// Riscv32E CPU（单周期）
// ---------------------------
class Riscv32E extends Module {
  val io = IO(new Bundle {
    val pc   = Output(UInt(DataWidth.W))
    val inst = Input(UInt(DataWidth.W))

    val memRen   = Output(Bool())
    val memWen   = Output(Bool())
    val memLen   = Output(UInt((DataWidth/8).W))
    val memAddr  = Output(UInt(DataWidth.W))
    val memWdata = Output(UInt(DataWidth.W))
    val memRdata = Input(UInt(DataWidth.W))
  })

  val ifu = Module(new IFU)
  val idu = Module(new IDU)
  val exu = Module(new EXU)
  val lsu = Module(new LSU)
  val wbu = Module(new WBU)

  // IFU
  io.pc := ifu.io.pc
  ifu.io.bren   := exu.io.bren
  ifu.io.braddr := exu.io.braddr
  ifu.io.halt   := idu.io.halt
  // IDU
  idu.io.pc   := ifu.io.pc
  idu.io.npc  := ifu.io.npc
  idu.io.inst := io.inst
  idu.io.wben   := wbu.io.wben
  idu.io.wbAddr := wbu.io.wbAddr
  idu.io.wbData := wbu.io.wbData
  // EXU
  exu.io.pc    := idu.io.pc
  exu.io.op1   := idu.io.op1
  exu.io.op2   := idu.io.op2
  exu.io.immsb := idu.io.immsb
  exu.io.exsel := idu.io.exsel
  // LSU
  lsu.io.memsel := idu.io.memsel
  lsu.io.addr   := exu.io.aluout
  lsu.io.data   := idu.io.RS2
  io.memRen   := lsu.io.memRen
  io.memWen   := lsu.io.memWen
  io.memLen   := lsu.io.memLen
  io.memAddr  := lsu.io.memAddr
  io.memWdata := lsu.io.memWdata
  // WBU
  wbu.io.wbsel   := idu.io.wbsel
  wbu.io.wbrd    := idu.io.wbrd
  wbu.io.memsel  := idu.io.memsel
  wbu.io.pc      := idu.io.pc
  wbu.io.csr     := idu.io.op2
  wbu.io.exData  := exu.io.aluout
  wbu.io.memData := io.memRdata
}

// ---------------------------
// Riscv32E TOP：自包含 CPU + ROM + RAM
// ---------------------------
class Riscv32ETOP extends Module {
  val cpu = Module(new Riscv32E)
  val rom = Module(new ROM_DPI)
  val ram = Module(new RAM_DPI)
  // 指令取值
  rom.io.addr := cpu.io.pc
  cpu.io.inst := rom.io.data
  // 数据访存
  ram.io.clk   := clock
  ram.io.re    := cpu.io.memRen
  ram.io.we    := cpu.io.memWen
  ram.io.len   := cpu.io.memLen
  ram.io.addr  := cpu.io.memAddr
  ram.io.wdata := cpu.io.memWdata
  cpu.io.memRdata := ram.io.rdata
}
