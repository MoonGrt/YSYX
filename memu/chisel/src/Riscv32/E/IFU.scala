package riscv.e

import chisel3._
import chisel3.util._
import riscv.Constants._

// ---------------------------
// IFU 模块：Instruction Fetch
// ---------------------------
class IFU extends Module {
  val io = IO(new Bundle {
    val halt   = Input(Bool())  // halt 信号
    val bren   = Input(Bool())  // 跳转使能
    val braddr = Input(UInt(DataWidth.W))  // 跳转地址
    val pc     = Output(UInt(DataWidth.W))  // 当前 PC 输出
    val npc    = Output(UInt(DataWidth.W))  // 下一个 PC
  })
  val pc = RegInit("h80000000".U)
  io.npc := Mux(io.bren, io.braddr, pc + 4.U)  // next pc
  pc := Mux(io.halt, pc, io.npc)
  io.pc := pc
}
