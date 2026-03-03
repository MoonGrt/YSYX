package riscv

import chisel3._
import chisel3.util._

// ---------------------------
// 工具：符号扩展
// ---------------------------
object Sext {
  def apply(x: UInt, bits: Int): UInt = {
    Cat(Fill(32 - bits, x(bits - 1)), x)
  }
}
