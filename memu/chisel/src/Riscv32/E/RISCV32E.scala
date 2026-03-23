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

    val mem_re    = Output(Bool())
    val mem_we    = Output(Bool())
    val mem_len   = Output(UInt((DataWidth/8).W))
    val mem_addr  = Output(UInt(DataWidth.W))
    val mem_wdata = Output(UInt(DataWidth.W))
    val mem_rdata = Input(UInt(DataWidth.W))
  })

  val ifu = Module(new IFU)
  val idu = Module(new IDU)
  val exu = Module(new EXU)

  // IFU
  io.pc := ifu.io.pc
  ifu.io.bren   := exu.io.bren
  ifu.io.braddr := exu.io.braddr
  ifu.io.halt   := idu.io.halt

  // IDU
  idu.io.pc   := ifu.io.pc
  idu.io.npc  := ifu.io.npc
  idu.io.inst := io.inst

  // EXU
  exu.io.pc    := idu.io.pc
  exu.io.op1   := idu.io.op1
  exu.io.op2   := idu.io.op2
  exu.io.immsb := idu.io.immsb
  exu.io.exsel := idu.io.exsel

  // Memory
  val memType   = idu.io.memsel
  io.mem_re    := !reset.asBool && memType.isOneOf(MEM.RW, MEM.RH, MEM.RB, MEM.RHU, MEM.RBU)
  io.mem_we    := !reset.asBool && memType.isOneOf(MEM.WW, MEM.WH, MEM.WB)
  io.mem_addr  := exu.io.aluout
  io.mem_wdata := idu.io.RS2
  io.mem_len   := Mux(memType.isOneOf(MEM.WB, MEM.RB, MEM.RBU), 1.U,
                  Mux(memType.isOneOf(MEM.WH, MEM.RH, MEM.RHU), 2.U, 4.U))

  // Write Back
  idu.io.exData  := exu.io.aluout
  idu.io.memData := io.mem_rdata
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
  ram.io.re    := cpu.io.mem_re
  ram.io.we    := cpu.io.mem_we
  ram.io.len   := cpu.io.mem_len
  ram.io.addr  := cpu.io.mem_addr
  ram.io.wdata := cpu.io.mem_wdata
  cpu.io.mem_rdata := ram.io.rdata
}
