package riscv.util

import chisel3._
import chisel3.util._
import riscv.Constants._

// ---------------------------
// Symbol Expansion
// ---------------------------
object Sext {
  def apply(x: UInt, bits: Int): UInt = {
    Cat(Fill(DataWidth - bits, x(bits - 1)), x)
  }
}

// ---------------------------
// Fibonacci Linear Feedback Shift Register
// ---------------------------
// taps: Polynomial masking (x^16 + x^14 + x^13 + x^11 + 1 > BigInt("1011_0100_0000_0000", 2))
class LFSR(
  val width: Int,
  val seed: BigInt,
  val taps: BigInt
) extends Module {
  require(width > 0)
  require(seed  > 0, "Seed must be non-zero for LFSR")
  require(taps  > 0, "Taps must be non-zero")
  val io = IO(new Bundle {
    val en   = Input(Bool())
    val data = Output(UInt(width.W))
  })
  val state = RegInit(seed.U(width.W))
  val feedback = (0 until width).map { i =>
    if (((taps >> i) & 1) == 1) state(i) else false.B
  }.reduce(_ ^ _)
  when(io.en) {
    state := Cat(state(width - 2, 0), feedback)
  }
  io.data := state
}
