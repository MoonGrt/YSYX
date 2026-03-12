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
      val NONE, RW, RH, RB, RHU, RBU, WW, WH, WB = Value
    }
    object CSRS extends ChiselEnum {
      val NONE, W, S, C, B, E, MRET = Value
    }
    object CSRI extends ChiselEnum {
      val MSTATUS, MTVEC, MEPC, MCAUSE,
          MCYCLE, MCYCLEH, MVENDORID, MARCHID, NONE = Value
    }
    val CSRADDR = Seq(
      0x300.U,  // mstatus
      0x305.U,  // mepc
      0x341.U,  // mcause
      0x342.U,  // mtvec
      0xB00.U,  // mcycle
      0xB80.U,  // mcycleh
      0xF11.U,  // mvendorid
      0xF12.U,  // marchid
    )
    def decodeCSR(addr: UInt): UInt = {
      MuxLookup(addr, CSRID.NONE.asUInt)(
        csrAddrTable.zipWithIndex.map { case (a, i) => a -> i.U }
      )
    }
  }
}
