package riscv.util

import chisel3._
import chisel3.util._
import riscv.Instructions._
import riscv.Constants.Riscv32E._
import riscv.Parameters.Riscv32E._

// ---------------------------
// DPI Mem BlackBox (数据存储器)
// ---------------------------
class DpiMem extends BlackBox{
  val io = IO(new Bundle {
    val ren   =  Input(Bool())
    val wen   =  Input(Bool())
    val mask  =  Input(UInt( 8.W))
    val addr  =  Input(UInt(32.W))
    val wdata =  Input(UInt(32.W))
    val rdata = Output(UInt(32.W))
  })
}

// ---------------------------
// DPI Exception BlackBox (异常处理模块)
// ---------------------------
class DpiExceptionBB extends BlackBox {
  val io = IO(new Bundle {
    val clk  = Input(Clock())
    val en   = Input(Bool())
    val code = Input(UInt(8.W))
  })
}

class Trap(val impled: Seq[BitPat]) extends Module {
  val io = IO(new Bundle {
    val valid = Input(Bool())
    val inst  = Input(UInt(DataWidth.W))
    val halt  = Output(Bool())
  })
  // -------- 异常类型 --------
  val is_ebreak = io.valid && (io.inst === EBREAK)
  val is_ecall  = io.valid && (io.inst === ECALL)
  val is_zero   = io.valid && (io.inst === 0.U)
  val is_impl   = io.valid && VecInit(impled.map(_ === io.inst)).asUInt.orR
  val is_unimpl = io.valid && ~is_impl
  val ecode = MuxCase(0.U, Seq(
    is_ebreak -> 0.U,
    is_ecall  -> 1.U,
    is_zero   -> 2.U,
    is_unimpl -> 3.U,
  ))
  // -------- Exception --------
  val exception = Module(new DpiExceptionBB)
  exception.io.clk  := clock
  exception.io.en   := io.valid && ~reset.asBool && 
                       (is_unimpl || is_zero || is_ebreak || is_ecall)
  exception.io.code := ecode
  // -------- halt --------
  io.halt := io.valid && ~reset.asBool && is_unimpl
}

// ---------------------------
// DPI DiffTest BlackBox (差分测试模块)
// ---------------------------
class DpiDiffPCBB extends BlackBox {
  val io = IO(new Bundle {
    val clk  = Input(Clock())
    val en   = Input(Bool())
    val pc   = Input(UInt(DataWidth.W))
    val npc  = Input(UInt(DataWidth.W))
    val inst = Input(UInt(DataWidth.W))
  })
}
class DpiDiffGPRBB extends BlackBox {
  val io = IO(new Bundle {
    val gpr  = Input(Vec(GPRNum, UInt(DataWidth.W)))
  })
}
class DpiDiffCSRBB extends BlackBox {
  val io = IO(new Bundle {
    val csr  = Input(Vec(CSRNum, UInt(DataWidth.W)))
  })
}
