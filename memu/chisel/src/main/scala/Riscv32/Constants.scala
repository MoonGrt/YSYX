package riscv

import chisel3._
import chisel3.util._

object Constants {
  // MiniRV Constants
  object MiniRV {
    val DataWidth = 32
    val GPRNum    = 16
    val CSRNum    = 8
    val CSRWidth  = 12
    object OP2 extends ChiselEnum {
      val NONE, RS2, IMI, IMS, IMU = Value
    }
    object EX extends ChiselEnum {
      val NONE, ADD, JAL = Value
    }
    object GPR extends ChiselEnum {
      val NONE, PC, EX, MEM = Value
    }
    object MEM extends ChiselEnum {
      val NONE, RW, RBU, WW, WB = Value
    }
  }
  // MiniRV Constants
  object Riscv32E {
    val DataWidth = 32
    val GPRNum    = 16
    val CSRNum    = 8
    val CSRWidth  = 12
    object OP1 extends ChiselEnum {
      val NONE, RS1, PC, IMZ = Value
    }
    object OP2 extends ChiselEnum {
      val NONE, RS2, CSR, IMI, IMS, IMJ, IMU = Value
    }
    object EX extends ChiselEnum {
      val NONE, ADD, SUB, AND, OR, XOR, SLL, SRL, SRA, SLT, SLTU, 
          BEQ, BNE, BLT, BGE, BLTU, BGEU, JAL, CSR = Value
    }
    object GPR extends ChiselEnum {
      val NONE, PC, EX, LS, CSR = Value
    }
    object LS extends ChiselEnum {
      val NONE, RW, RH, RB, RHU, RBU, WW, WH, WB = Value
    }
    object CSR extends ChiselEnum {
      val NONE, W, S, C, B, E, MRET = Value
    }
  }
}
