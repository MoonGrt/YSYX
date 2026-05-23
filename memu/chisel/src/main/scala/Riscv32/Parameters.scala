package riscv

import chisel3._
import chisel3.util._
import peripheral.mem._

object Parameters {
  // MiniRV Parameters
  object MiniRV {
    // Basic
    val DataWidth = 32
    val GPRNum    = 16
    val CSRNum    = 8
    val CSRWidth  = 12
  }
  // Riscv32E Parameters
  object Riscv32E {
    // Basic
    val DataWidth = 32
    val GPRNum    = 16
    val CSRNum    = 8
    val CSRWidth  = 12
    // Mem
    val memBusType  = BusType.AXI
    val memUseDpi   = true
    val memDelayCfg = MemDelayConfig(
      enable = false,
      delayWidth = 8,
      delaySeed = 2,
      delayTaps = 0x9
    )
  }
}

object Constants {
  // MiniRV Constants
  object MiniRV {
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
  // Riscv32E Constants
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
