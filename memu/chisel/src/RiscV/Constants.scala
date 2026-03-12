package riscv

import chisel3._
import chisel3.util._

object Constants {
  val WORD_LEN = 32
  val CSR_NUM  = 8
  val GPR_NUM  = 32

  object MiniRV {
    object IMM extends ChiselEnum {
      val N, I, S, U = Value
    }
    object EX extends ChiselEnum {
      val ADD, JALR = Value
    }
    object JUMP extends ChiselEnum {
      val NONE, JALR = Value
    }
    object WB extends ChiselEnum {
      val NONE, EX, MEM = Value
    }
    object MEM extends ChiselEnum {
      val NONE, RW, RB, WW, WB = Value
    }
  }

  object Riscv32E {
    object OP1 extends ChiselEnum {
      val RS1, PC, IMZ, NONE = Value
    }
    object OP2 extends ChiselEnum {
      val RS2, CSR, IMI, IMS, IMJ, IMU, NONE = Value
    }
    object EX extends ChiselEnum {
      val NONE, ADD, SUB, AND, OR, XOR, SLL, SRL, SRA, SLT, SLTU, 
          BEQ, BNE, BLT, BGE, BLTU, BGEU, JAL, CSR = Value
    }
    object WB extends ChiselEnum {
      val PC, EX, MEM, CSR, NONE = Value
    }
    object MEM extends ChiselEnum {
      val NONE, RW, RB, WW, WB = Value
    }
    object CSRS extends ChiselEnum {  // 
      val NONE, W, S, C, B, E, MRET = Value
    }

    val MEM_SEL_LEN = 4
    val MEM_NONE = 0.U(MEM_SEL_LEN.W)
    val MEM_RW   = 1.U(MEM_SEL_LEN.W)  // read word
    val MEM_RH   = 2.U(MEM_SEL_LEN.W)  // read half word
    val MEM_RB   = 3.U(MEM_SEL_LEN.W)  // read byte
    val MEM_RHU  = 4.U(MEM_SEL_LEN.W)  // read half word unsigned
    val MEM_RBU  = 5.U(MEM_SEL_LEN.W)  // read byte unsigned
    val MEM_WW   = 6.U(MEM_SEL_LEN.W)
    val MEM_WH   = 7.U(MEM_SEL_LEN.W)
    val MEM_WB   = 8.U(MEM_SEL_LEN.W)
  }
}
