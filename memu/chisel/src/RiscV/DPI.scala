package riscv

import chisel3._
import chisel3.util._

// ---------------------------
// ROM BlackBox (只读指令存储器)
// ---------------------------
class ROM_DPI extends BlackBox{
  val io = IO(new Bundle {
    val addr = Input(UInt(32.W))
    val data = Output(UInt(32.W))
  })
}

// ---------------------------
// RAM BlackBox (可读写数据存储器)
// ---------------------------
class RAM_DPI extends BlackBox {
  val io = IO(new Bundle {
    val re    = Input(Bool())
    val we    = Input(Bool())
    val len   = Input(UInt(8.W))
    val addr  = Input(UInt(32.W))
    val wdata = Input(UInt(32.W))
    val rdata = Output(UInt(32.W))
  })
}

// ---------------------------
// EBreak BlackBox (异常处理模块)
// ---------------------------
class EBreak extends BlackBox {
  val io = IO(new Bundle {
    val clk  = Input(Clock())
    val trap = Input(Bool())
    val code = Input(UInt(8.W))
  })
}

// ---------------------------
// DiffTest BlackBox (差分测试模块)
// ---------------------------
class DiffTest extends BlackBox {
  val io = IO(new Bundle {
    val clk  = Input(Clock())
    val pc   = Input(UInt(32.W))
    val npc  = Input(UInt(32.W))
    val inst = Input(UInt(32.W))
    val gpr  = Input(Vec(32, UInt(32.W)))
    val csr  = Input(Vec(4, UInt(32.W)))
  })
}
