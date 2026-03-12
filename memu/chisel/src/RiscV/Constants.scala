package riscv

import chisel3._
import chisel3.util._

object Constants {
  val WORD_LEN = 32
  val CSR_NUM  = 8
  val GPR_NUM  = 32

  object MiniRV_Constants {
    val IMM_SEL_LEN = 2
    val IMMN = 0.U(IMM_SEL_LEN.W)
    val IMMI = 1.U(IMM_SEL_LEN.W)
    val IMMS = 2.U(IMM_SEL_LEN.W)
    val IMMU = 3.U(IMM_SEL_LEN.W)

    val EX_SEL_LEN = 1
    val EX_ADD  = 0.U(EX_SEL_LEN.W)
    val EX_JALR = 1.U(EX_SEL_LEN.W)

    val JUMP_SEL_LEN = 1
    val JUMP_NONE = 0.U(JUMP_SEL_LEN.W)
    val JUMP_JALR = 1.U(JUMP_SEL_LEN.W)

    val WB_SEL_LEN = 2
    val WB_NONE = 0.U(WB_SEL_LEN.W)
    val WB_EX   = 1.U(WB_SEL_LEN.W)
    val WB_MEM  = 2.U(WB_SEL_LEN.W)

    val MEM_SEL_LEN = 3
    val MEM_NONE = 0.U(MEM_SEL_LEN.W)
    val MEM_RW   = 1.U(MEM_SEL_LEN.W)  // write word
    val MEM_RB   = 2.U(MEM_SEL_LEN.W)  // write byte
    val MEM_WW   = 3.U(MEM_SEL_LEN.W)
    val MEM_WB   = 4.U(MEM_SEL_LEN.W)
  }

  object Riscv32E_Constants {
    val OP1_SEL_LEN = 2
    val OP1_RS1  = 0.U(OP1_SEL_LEN.W)
    val OP1_PC   = 1.U(OP1_SEL_LEN.W)
    val OP1_IMZ  = 2.U(OP1_SEL_LEN.W)
    val OP1_NONE = 3.U(OP1_SEL_LEN.W)

    val OP2_SEL_LEN = 3
    val OP2_NONE = 0.U(OP2_SEL_LEN.W)
    val OP2_RS2  = 1.U(OP2_SEL_LEN.W)
    val OP2_CSR  = 2.U(OP2_SEL_LEN.W)
    val OP2_IMI  = 3.U(OP2_SEL_LEN.W)
    val OP2_IMS  = 4.U(OP2_SEL_LEN.W)
    val OP2_IMJ  = 5.U(OP2_SEL_LEN.W)
    val OP2_IMU  = 6.U(OP2_SEL_LEN.W)

    val EX_SEL_LEN = 5
    val EX_NONE =  0.U(EX_SEL_LEN.W)
    val EX_ADD  =  1.U(EX_SEL_LEN.W)
    val EX_SUB  =  2.U(EX_SEL_LEN.W)
    val EX_AND  =  3.U(EX_SEL_LEN.W)
    val EX_OR   =  4.U(EX_SEL_LEN.W)
    val EX_XOR  =  5.U(EX_SEL_LEN.W)
    val EX_SLL  =  6.U(EX_SEL_LEN.W)
    val EX_SRL  =  7.U(EX_SEL_LEN.W)
    val EX_SRA  =  8.U(EX_SEL_LEN.W)
    val EX_SLT  =  9.U(EX_SEL_LEN.W)
    val EX_SLTU = 10.U(EX_SEL_LEN.W)
    val EX_BEQ  = 11.U(EX_SEL_LEN.W)
    val EX_BNE  = 12.U(EX_SEL_LEN.W)
    val EX_BLT  = 13.U(EX_SEL_LEN.W)
    val EX_BGE  = 14.U(EX_SEL_LEN.W)
    val EX_BLTU = 15.U(EX_SEL_LEN.W)
    val EX_BGEU = 16.U(EX_SEL_LEN.W)
    val EX_JAL  = 17.U(EX_SEL_LEN.W)
    val EX_CSR  = 18.U(EX_SEL_LEN.W)

    val WB_SEL_LEN = 3
    val WB_NONE = 0.U(WB_SEL_LEN.W)
    val WB_PC   = 1.U(WB_SEL_LEN.W)
    val WB_EX   = 2.U(WB_SEL_LEN.W)
    val WB_MEM  = 3.U(WB_SEL_LEN.W)
    val WB_CSR  = 4.U(WB_SEL_LEN.W)

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

    val CSR_SEL_LEN  = 3
    val CSR_NONE = 0.U(CSR_SEL_LEN.W)
    val CSR_W    = 1.U(CSR_SEL_LEN.W)  // Write
    val CSR_S    = 2.U(CSR_SEL_LEN.W)  // Set bits
    val CSR_C    = 3.U(CSR_SEL_LEN.W)  // Clear bits
    val CSR_B    = 4.U(CSR_SEL_LEN.W)  // Break
    val CSR_E    = 5.U(CSR_SEL_LEN.W)  // Exception (ECALL)
    val CSR_MRET = 6.U(CSR_SEL_LEN.W)  // Return from exception
  }
}
