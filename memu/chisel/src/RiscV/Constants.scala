package riscv

import chisel3._
import chisel3.util._

abstract class ConstEnum extends ChiselEnum {
  def len: Int = log2Ceil(this.getWidth)
}

object CtrlEnum {

  /**  
   * 自动生成 Enum 和常量
   * @param namePrefix 前缀，比如 "OP1", "EX"
   * @param options   选项列表，顺序决定 UInt 值
   * @return (宽度, list of UInt constants)
   */
  def define(namePrefix: String, options: Seq[String]): (Int, Seq[UInt]) = {
    val width = log2Ceil(options.length max 2) // 最小宽度 1 bit
    val enum1 = Enum(options.length)
    val constants = enum1.toSeq
    // 打印方便调试
    println(s"$namePrefix width = $width, constants = ${options.zip(constants)}")
    (width, constants)
  }
}

object Constants {
  val WORD_LEN = 32
  val CSR_NUM  = 8
  val GPR_NUM  = 32

import chisel3._
import chisel3.util._

object MiniRV {

  // 自动生成常量和宽度
  private def makeConsts(names: Seq[String]): (Seq[UInt], Int) = {
    val width = log2Ceil(names.size)
    val consts = names.indices.map(i => i.U(width.W))
    (consts, width)
  }

  // IMM
  private val (immSeq, immWidth) = makeConsts(Seq("IMMN", "IMMI", "IMMS", "IMMU"))
  val IMM_SEL_LEN = immWidth
  val IMMN = immSeq(0)
  val IMMI = immSeq(1)
  val IMMS = immSeq(2)
  val IMMU = immSeq(3)

  // EX
  private val (exSeq, exWidth) = makeConsts(Seq("EX_ADD", "EX_JALR"))
  val EX_SEL_LEN = exWidth
  val EX_ADD = exSeq(0)
  val EX_JALR = exSeq(1)

  // JUMP
  private val (jumpSeq, jumpWidth) = makeConsts(Seq("JUMP_NONE", "JUMP_JALR"))
  val JUMP_SEL_LEN = jumpWidth
  val JUMP_NONE = jumpSeq(0)
  val JUMP_JALR = jumpSeq(1)

  // WB
  private val (wbSeq, wbWidth) = makeConsts(Seq("WB_NONE", "WB_EX", "WB_MEM"))
  val WB_SEL_LEN = wbWidth
  val WB_NONE = wbSeq(0)
  val WB_EX   = wbSeq(1)
  val WB_MEM  = wbSeq(2)

  // MEM
  private val (memSeq, memWidth) = makeConsts(Seq("MEM_NONE", "MEM_RW", "MEM_RB", "MEM_WW", "MEM_WB"))
  val MEM_SEL_LEN = memWidth
  val MEM_NONE = memSeq(0)
  val MEM_RW   = memSeq(1)
  val MEM_RB   = memSeq(2)
  val MEM_WW   = memSeq(3)
  val MEM_WB   = memSeq(4)
}

  object Riscv32E {
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
