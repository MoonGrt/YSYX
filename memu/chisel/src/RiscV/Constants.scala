package riscv

import chisel3._
import chisel3.util._

object Constants {
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

  // object MiniRV {
  //   object OP2 extends ChiselEnum {
  //     val NONE, RS2, IMI, IMS, IMU = Value
  //   }
  //   object EX extends ChiselEnum {
  //     val NONE, ADD, JAL = Value
  //   }
  //   object WB extends ChiselEnum {
  //     val NONE, PC, EX, MEM = Value
  //   }
  //   object MEM extends ChiselEnum {
  //     val NONE, RW, RBU, WW, WB = Value
  //   }
  // }

  object Riscv32E {
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
    object WB extends ChiselEnum {
      val NONE, PC, EX, MEM, CSR = Value
    }
    object MEM extends ChiselEnum {
      val NONE, RW, RH, RB, RHU, RBU, WW, WH, WB = Value
    }
    object CSRS extends ChiselEnum {
      val NONE, W, S, C, B, E, MRET = Value
    }
  }
}
