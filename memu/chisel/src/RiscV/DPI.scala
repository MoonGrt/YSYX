package riscv

import chisel3._
import chisel3.util._
import CoreConstants._

// ---------------------------
// ROM BlackBox (只读指令存储器)
// ---------------------------
class ROM_DPI extends BlackBox{
  val io = IO(new Bundle {
    val addr = Input(UInt(WORD_LEN.W))
    val data = Output(UInt(WORD_LEN.W))
  })
}

// ---------------------------
// RAM BlackBox (可读写数据存储器)
// ---------------------------
class RAM_DPI extends BlackBox {
  val io = IO(new Bundle {
    val clk   = Input(Clock())
    val re    = Input(Bool())
    val we    = Input(Bool())
    val len   = Input(UInt(8.W))
    val addr  = Input(UInt(WORD_LEN.W))
    val wdata = Input(UInt(WORD_LEN.W))
    val rdata = Output(UInt(WORD_LEN.W))
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
    val pc   = Input(UInt(WORD_LEN.W))
    val npc  = Input(UInt(WORD_LEN.W))
    val inst = Input(UInt(WORD_LEN.W))
    val csr  = Input(Vec(CSR_NUM, UInt(WORD_LEN.W)))
    val gpr  = Input(Vec(GPR_NUM, UInt(WORD_LEN.W)))
  })
}
