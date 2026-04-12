package riscv.util

import chisel3._
import chisel3.util._
import riscv.Constants._

// ---------------------------
// 工具：符号扩展
// ---------------------------
object Sext {
  def apply(x: UInt, bits: Int): UInt = {
    Cat(Fill(DataWidth - bits, x(bits - 1)), x)
  }
}
