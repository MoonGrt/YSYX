package riscv

import chisel3._
import chisel3.util._

// ---------------------------
// Configuration parameters
// ---------------------------
object Riscv32E_Instructions {
  // Load/Store
  val LW     = BitPat("b?????????????????010?????0000011")
  val LBU    = BitPat("b?????????????????100?????0000011")
  val SW     = BitPat("b?????????????????010?????0100011")
  val SB     = BitPat("b?????????????????000?????0100011")
  // Add/Sub
  val ADD    = BitPat("b0000000??????????000?????0110011")
  val ADDI   = BitPat("b?????????????????000?????0010011")
  val SUB    = BitPat("b0100000??????????000?????0110011")
  // Logical operations
  val AND    = BitPat("b0000000??????????111?????0110011")
  val OR     = BitPat("b0000000??????????110?????0110011")
  val XOR    = BitPat("b0000000??????????100?????0110011")
  val ANDI   = BitPat("b?????????????????111?????0010011")
  val ORI    = BitPat("b?????????????????110?????0010011")
  val XORI   = BitPat("b?????????????????100?????0010011")
  // Shift
  val SLL    = BitPat("b0000000??????????001?????0110011")
  val SRL    = BitPat("b0000000??????????101?????0110011")
  val SRA    = BitPat("b0100000??????????101?????0110011")
  val SLLI   = BitPat("b0000000??????????001?????0010011")
  val SRLI   = BitPat("b0000000??????????101?????0010011")
  val SRAI   = BitPat("b0100000??????????101?????0010011")
  // Compare
  val SLT    = BitPat("b0000000??????????010?????0110011")
  val SLTU   = BitPat("b0000000??????????011?????0110011")
  val SLTI   = BitPat("b?????????????????010?????0010011")
  val SLTIU  = BitPat("b?????????????????011?????0010011")
  // Branch
  val BEQ    = BitPat("b?????????????????000?????1100011")
  val BNE    = BitPat("b?????????????????001?????1100011")
  val BLT    = BitPat("b?????????????????100?????1100011")
  val BGE    = BitPat("b?????????????????101?????1100011")
  val BLTU   = BitPat("b?????????????????110?????1100011")
  val BGEU   = BitPat("b?????????????????111?????1100011")

  // Jump
  val JAL    = BitPat("b?????????????????????????1101111")
  val JALR   = BitPat("b?????????????????000?????1100111")
  // Load immediate
  val LUI    = BitPat("b?????????????????????????0110111")
  val AUIPC  = BitPat("b?????????????????????????0010111")

  // CSR
  val CSRRW  = BitPat("b?????????????????001?????1110011")
  val CSRRWI = BitPat("b?????????????????101?????1110011")
  val CSRRS  = BitPat("b?????????????????010?????1110011")
  val CSRRSI = BitPat("b?????????????????110?????1110011")
  val CSRRC  = BitPat("b?????????????????011?????1110011")
  val CSRRCI = BitPat("b?????????????????111?????1110011")

  // Exception
  val E      = BitPat("b?????????????????????????1110011")
  val EBREAK = BitPat("b00000000000100000000000001110011")

  // Implemented instructions
  val IMPLED = Seq(
    LW, LBU, SW, SB,
    ADD, ADDI, SUB, AND, OR, XOR, ANDI, ORI, XORI,
    SLL, SRL, SRA, SLLI, SRLI, SRAI, SLT, SLTU, SLTI, SLTIU,
    BEQ, BNE, BLT, BGE, BLTU, BGEU,
    JAL, JALR, LUI, AUIPC,
    CSRRW, CSRRWI, CSRRS, CSRRSI, CSRRC, CSRRCI,
    E, EBREAK,
  )
}
object Riscv32E_Parameters {
  val WORD_LEN = 32

  val OP1_SEL_LEN = 2
  val OP1_RS1  = 0.U(OP1_SEL_LEN.W)
  val OP1_PC   = 1.U(OP1_SEL_LEN.W)
  val OP1_IMZ  = 2.U(OP1_SEL_LEN.W)
  val OP1_NONE = 3.U(OP1_SEL_LEN.W)

  val OP2_SEL_LEN = 3
  val OP2_NONE = 0.U(OP2_SEL_LEN.W)
  val OP2_RS2  = 1.U(OP2_SEL_LEN.W)
  val OP2_IMI  = 2.U(OP2_SEL_LEN.W)
  val OP2_IMS  = 3.U(OP2_SEL_LEN.W)
  val OP2_IMJ  = 4.U(OP2_SEL_LEN.W)
  val OP2_IMU  = 5.U(OP2_SEL_LEN.W)

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

  val WB_SEL_LEN = 3
  val WB_NONE = 0.U(WB_SEL_LEN.W)
  val WB_PC   = 1.U(WB_SEL_LEN.W)
  val WB_EX   = 2.U(WB_SEL_LEN.W)
  val WB_MEM  = 3.U(WB_SEL_LEN.W)
  val WB_CSR  = 4.U(WB_SEL_LEN.W)

  val MEM_SEL_LEN = 3
  val MEM_NONE = 0.U(MEM_SEL_LEN.W)
  val MEM_RW   = 1.U(MEM_SEL_LEN.W)  // write word
  val MEM_RB   = 2.U(MEM_SEL_LEN.W)  // write byte
  val MEM_WW   = 3.U(MEM_SEL_LEN.W)
  val MEM_WB   = 4.U(MEM_SEL_LEN.W)

  val CSR_LEN  = 3
  val CSR_NONE = 0.U(CSR_LEN.W)
  val CSR_W    = 1.U(CSR_LEN.W)  // Write
  val CSR_S    = 2.U(CSR_LEN.W)  // Set bits
  val CSR_C    = 3.U(CSR_LEN.W)  // Clear bits
  val CSR_E    = 4.U(CSR_LEN.W)  // Exception (ECALL)
  val CSR_V    = 5.U(CSR_LEN.W)
}

// ---------------------------
// IF 模块：Instruction Fetch
// ---------------------------
class Riscv32E_IF extends Module {
  import Riscv32E_Parameters._
  val io = IO(new Bundle {
    val halt   = Input(Bool())  // halt 信号
    val bren   = Input(Bool())  // 跳转使能
    val braddr = Input(UInt(WORD_LEN.W))  // 跳转地址
    val npc    = Output(UInt(WORD_LEN.W))  // 下一个 PC
    val pc     = Output(UInt(WORD_LEN.W))  // 当前 PC 输出
  })
  val pc = RegInit("h80000000".U(WORD_LEN.W))
  pc := MuxCase(io.npc, Seq(
    io.halt -> pc,
    io.bren -> io.braddr,
  ))
  io.pc  := pc
  io.npc := pc + 4.U
}

// ---------------------------
// ID 模块：Instruction Decode + GPR
// ---------------------------
class Riscv32E_ID extends Module {
  import Riscv32E_Instructions._
  import Riscv32E_Parameters._
  val io = IO(new Bundle {
    val pc      = Input(UInt(WORD_LEN.W))
    val inst    = Input(UInt(WORD_LEN.W))

    // 写回接口（来自 WB）
    val wb_en   = Input(Bool())
    val wb_rd   = Input(UInt(5.W))
    val wb_data = Input(UInt(WORD_LEN.W))

    // 输出到 EX
    val exsel   = Output(UInt(EX_SEL_LEN.W))
    val op1     = Output(UInt(WORD_LEN.W))
    val op2     = Output(UInt(WORD_LEN.W))
    val immsb   = Output(UInt(WORD_LEN.W))
    val rs2     = Output(UInt(WORD_LEN.W))
    val rd_addr = Output(UInt(5.W))

    // Control signals
    val halt   = Output(Bool())
    val memBen = Output(Bool())
    val memRen = Output(Bool())
    val memWen = Output(Bool())
    val regWen = Output(Bool())

    // Diff
    val gprOut = Output(Vec(32, UInt(WORD_LEN.W)))
    val csrOut = Output(Vec(4, UInt(WORD_LEN.W)))
  })

  val List(op1sel, op2sel, exsel, wbsel, memsel, csrsel) = ListLookup(
    io.inst,
    List(OP1_RS1, OP2_RS2, EX_ADD, WB_EX, MEM_NONE, CSR_NONE),
    Array(
      LW     -> List(OP1_RS1 , OP2_IMI , EX_ADD , WB_MEM , MEM_RW  , CSR_NONE),  // x[rs1] + sext(immi)
      LBU    -> List(OP1_RS1 , OP2_IMI , EX_ADD , WB_MEM , MEM_RB  , CSR_NONE),  // x[rs1] + sext(immi)
      SW     -> List(OP1_RS1 , OP2_IMS , EX_ADD , WB_NONE, MEM_WW  , CSR_NONE),  // x[rs1] + sext(imms)
      SB     -> List(OP1_RS1 , OP2_IMS , EX_ADD , WB_NONE, MEM_WB  , CSR_NONE),  // x[rs1] + sext(imms)

      ADD    -> List(OP1_RS1 , OP2_RS2 , EX_ADD , WB_EX  , MEM_NONE, CSR_NONE),  // x[rs1] + x[rs2]
      ADDI   -> List(OP1_RS1 , OP2_IMI , EX_ADD , WB_EX  , MEM_NONE, CSR_NONE),  // x[rs1] + sext(immi)
      SUB    -> List(OP1_RS1 , OP2_RS2 , EX_SUB , WB_EX  , MEM_NONE, CSR_NONE),  // x[rs1] - x[rs2]
      AND    -> List(OP1_RS1 , OP2_RS2 , EX_AND , WB_EX  , MEM_NONE, CSR_NONE),  // x[rs1] & x[rs2]
      OR     -> List(OP1_RS1 , OP2_RS2 , EX_OR  , WB_EX  , MEM_NONE, CSR_NONE),  // x[rs1] | x[rs2]
      XOR    -> List(OP1_RS1 , OP2_RS2 , EX_XOR , WB_EX  , MEM_NONE, CSR_NONE),  // x[rs1] ^ x[rs2]
      ANDI   -> List(OP1_RS1 , OP2_IMI , EX_AND , WB_EX  , MEM_NONE, CSR_NONE),  // x[rs1] & sext(immi)
      ORI    -> List(OP1_RS1 , OP2_IMI , EX_OR  , WB_EX  , MEM_NONE, CSR_NONE),  // x[rs1] | sext(immi)
      XORI   -> List(OP1_RS1 , OP2_IMI , EX_XOR , WB_EX  , MEM_NONE, CSR_NONE),  // x[rs1] ^ sext(immi)
      SLL    -> List(OP1_RS1 , OP2_RS2 , EX_SLL , WB_EX  , MEM_NONE, CSR_NONE),  // x[rs1] << x[rs2](4,0)
      SRL    -> List(OP1_RS1 , OP2_RS2 , EX_SRL , WB_EX  , MEM_NONE, CSR_NONE),  // x[rs1] >>u x[rs2](4,0)
      SRA    -> List(OP1_RS1 , OP2_RS2 , EX_SRA , WB_EX  , MEM_NONE, CSR_NONE),  // x[rs1] >>s x[rs2](4,0)
      SLLI   -> List(OP1_RS1 , OP2_IMI , EX_SLL , WB_EX  , MEM_NONE, CSR_NONE),  // x[rs1] << immsi(4,0)
      SRLI   -> List(OP1_RS1 , OP2_IMI , EX_SRL , WB_EX  , MEM_NONE, CSR_NONE),  // x[rs1] >>u immsi(4,0)
      SRAI   -> List(OP1_RS1 , OP2_IMI , EX_SRA , WB_EX  , MEM_NONE, CSR_NONE),  // x[rs1] >>s immsi(4,0)
      SLT    -> List(OP1_RS1 , OP2_RS2 , EX_SLT , WB_EX  , MEM_NONE, CSR_NONE),  // x[rs1] <s x[rs2]
      SLTU   -> List(OP1_RS1 , OP2_RS2 , EX_SLTU, WB_EX  , MEM_NONE, CSR_NONE),  // x[rs1] <u x[rs2]
      SLTI   -> List(OP1_RS1 , OP2_IMI , EX_SLT , WB_EX  , MEM_NONE, CSR_NONE),  // x[rs1] <s immsi
      SLTIU  -> List(OP1_RS1 , OP2_IMI , EX_SLTU, WB_EX  , MEM_NONE, CSR_NONE),  // x[rs1] <u immsi

      BEQ    -> List(OP1_RS1 , OP2_RS2 , EX_BEQ , WB_NONE, MEM_NONE, CSR_NONE),  // x[rs1] === x[rs2] then PC+sext(imm_b)
      BNE    -> List(OP1_RS1 , OP2_RS2 , EX_BNE , WB_NONE, MEM_NONE, CSR_NONE),  // x[rs1] =/= x[rs2] then PC+sext(imm_b)
      BGE    -> List(OP1_RS1 , OP2_RS2 , EX_BGE , WB_NONE, MEM_NONE, CSR_NONE),  // x[rs1] >=s x[rs2] then PC+sext(imm_b)
      BGEU   -> List(OP1_RS1 , OP2_RS2 , EX_BGEU, WB_NONE, MEM_NONE, CSR_NONE),  // x[rs1] >=u x[rs2] then PC+sext(imm_b)
      BLT    -> List(OP1_RS1 , OP2_RS2 , EX_BLT , WB_NONE, MEM_NONE, CSR_NONE),  // x[rs1] <s x[rs2]  then PC+sext(imm_b)
      BLTU   -> List(OP1_RS1 , OP2_RS2 , EX_BLTU, WB_NONE, MEM_NONE, CSR_NONE),  // x[rs1] <u x[rs2]  then PC+sext(imm_b)
      JAL    -> List(OP1_PC  , OP2_IMJ , EX_JAL , WB_PC  , MEM_NONE, CSR_NONE),  // x[rd] <- PC+4 and PC+sext(imm_j)
      JALR   -> List(OP1_RS1 , OP2_IMI , EX_JAL , WB_PC  , MEM_NONE, CSR_NONE),  // x[rd] <- PC+4 and (x[rs1]+sext(imm_i))&~1

      LUI    -> List(OP1_NONE, OP2_IMU , EX_ADD , WB_EX  , MEM_NONE, CSR_NONE),  // sext(immu[31:12] << 12)
      AUIPC  -> List(OP1_PC  , OP2_IMU , EX_ADD , WB_EX  , MEM_NONE, CSR_NONE),  // PC + sext(immu[31:12] << 12)

      CSRRW  -> List(OP1_RS1 , OP2_NONE, EX_ADD , WB_CSR , MEM_NONE, CSR_W   ), // CSRs[csr] <- x[rs1]
      CSRRWI -> List(OP1_IMZ , OP2_NONE, EX_ADD , WB_CSR , MEM_NONE, CSR_W   ), // CSRs[csr] <- uext(imm_z)
      CSRRS  -> List(OP1_RS1 , OP2_NONE, EX_ADD , WB_CSR , MEM_NONE, CSR_S   ), // CSRs[csr] <- CSRs[csr] | x[rs1]
      CSRRSI -> List(OP1_IMZ , OP2_NONE, EX_ADD , WB_CSR , MEM_NONE, CSR_S   ), // CSRs[csr] <- CSRs[csr] | uext(imm_z)
      CSRRC  -> List(OP1_RS1 , OP2_NONE, EX_ADD , WB_CSR , MEM_NONE, CSR_C   ), // CSRs[csr] <- CSRs[csr]&~x[rs1]
      CSRRCI -> List(OP1_IMZ , OP2_NONE, EX_ADD , WB_CSR , MEM_NONE, CSR_C   ), // CSRs[csr] <- CSRs[csr]&~uext(imm_z)
    ),
  )

  // -------- 寄存器堆 --------
  val GPR = RegInit(VecInit(Seq.fill(32)(0.U(WORD_LEN.W))))
  val CSR = RegInit(VecInit(Seq(  // 注意修改 csrOut 个数
    0x00000000.U,  // mstatus
    0x00000000.U,  // mepc
    0x00000000.U,  // mcause
    0x00000000.U,  // mtvec
    // 0x00000000.U,  // mvendorid
    // 0x00000000.U,  // marchid
  )))

  // -------- 指令字段 --------
  val rd  = io.inst(11,7)
  val rs1 = io.inst(19,15)
  val rs2 = io.inst(24,20)

  // -------- 立即数 --------
  // sext 12bit value to 32bit value.
  val immi = io.inst(31,20)  // imm for I-type
  val immsi = Cat(Fill(20, immi(11)), immi)
  val imms = Cat(io.inst(31,25), io.inst(11,7))  // imm for S-type
  val immss = Cat(Fill(12, imms(11)), imms)
  // Decode imm of B-type instruction
  val immb = Cat(io.inst(31), io.inst(7), io.inst(30,25), io.inst(11,8))
  val immsb = Cat(Fill(19, immb(11)), immb, 0.U(1.W))
  // Decode imm of J-type instruction
  val immj = Cat(io.inst(31), io.inst(19,12), io.inst(20), io.inst(30,21))
  val immsj = Cat(Fill(11, immj(19)), immj, 0.U(1.W))  // Set LSB to zero
  // Decode imm of U-type instruction
  val immu = Cat(io.inst(31,12), Fill(12, 0.U))  // for LUI and AUIPC
  // Decode imm of I-type instruction
  val immz = io.inst(19, 15)
  val immuz = Cat(Fill(27, 0.U), immz)  // for CSR instructions

  // -------- EX功能 --------
  io.exsel := exsel
  io.immsb := immsb
  io.rs2 := GPR(rs2)
  // Determine 1st operand data signal
  io.op1 := MuxCase(0.U(32.W), Seq(
    (op1sel === OP1_RS1) -> GPR(rs1),
    (op1sel === OP1_PC)  -> io.pc,
    (op1sel === OP1_IMZ) -> immuz,
  ))
  // Determine 2nd operand data signal
  io.op2 := MuxCase(0.U(32.W), Seq(
    (op2sel === OP2_RS2) -> GPR(rs2),
    (op2sel === OP2_IMI) -> immsi,
    (op2sel === OP2_IMS) -> immss,
    (op2sel === OP2_IMJ) -> immsj,
    (op2sel === OP2_IMU) -> immu,  // for LUI and AUIPC
  ))

  // -------- WB功能 --------
  // GPR
  io.rd_addr := rd
  io.memBen  := ~reset.asBool && ((memsel === MEM_RB) || (memsel === MEM_WB))
  io.memRen  := ~reset.asBool && ((memsel === MEM_RW) || (memsel === MEM_RB))
  io.memWen  := ~reset.asBool && ((memsel === MEM_WW) || (memsel === MEM_WB))
  io.regWen  := wbsel =/= WB_NONE
  when (io.wb_en && io.wb_rd =/= 0.U) {
    GPR(io.wb_rd) := Mux(
      wbsel === WB_PC, io.pc + 4.U, io.wb_data
    )
  }
  // CSR
  val csr_addr = immi
  val csr_id = MuxLookup(csr_addr(11,0), 0.U)(Seq(
    0x300.U -> 1.U,  // mstatus
    0x341.U -> 2.U,  // mepc
    0x342.U -> 3.U,  // mcause
    0x305.U -> 4.U,  // mtvec
    // 0xf11.U -> 5.U,  // mvendorid
    // 0xf12.U -> 6.U,  // marchid
  ))
  val csr_valid = csr_id =/= 0.U
  val csr_old   = Mux(csr_valid, CSR(csr_id), 0.U)
  val csr_new = MuxCase(csr_old, Seq(
    (csrsel === CSR_W) -> io.op1,
    (csrsel === CSR_S) -> (csr_old | io.op1),
    (csrsel === CSR_C) -> (csr_old & ~io.op1)
  ))
  when (~reset.asBool && csr_valid && csrsel =/= CSR_NONE) {
    CSR(csr_id) := csr_new
  }

  // -------- 异常处理 --------
  val trap = Module(new EBreak)
  // 定义异常编码规则
  // 0: EBREAK, 1: 全零指令, 2: 其他E指令, 3: 未实现指令
  val impl_inst = IMPLED.filterNot(inst =>
    inst == E || inst == EBREAK
  )
  val is_unimpl = ~impl_inst.map(inst => io.inst === inst).reduce(_ || _)
  val is_zero = (io.inst === 0.U)
  val is_ebreak = (io.inst === EBREAK)
  val is_otherE = (io.inst === E) && (io.inst =/= EBREAK)
  val exc_code = MuxCase(
    1.U(8.W),  // 默认全零指令
    Seq(
      is_ebreak -> 0.U,  // EBREAK
      is_zero -> 1.U,  // 全零指令
      is_otherE -> 2.U,  // 其他E指令
      is_unimpl -> 3.U  // 未实现指令
    )
  )
  // 输出到 EBreak 模块
  trap.io.clk  := clock
  trap.io.trap := ~reset.asBool && is_unimpl
  trap.io.code := exc_code
  // halt 信号
  io.halt := ~reset.asBool && is_unimpl
  // 输出 GPR
  io.gprOut := GPR
  io.csrOut := CSR
}

// ---------------------------
// EX 模块
// ---------------------------
class Riscv32E_EX extends Module {
  import Riscv32E_Parameters._
  val io = IO(new Bundle {
    val pc     = Input(UInt(WORD_LEN.W))
    val op1    = Input(UInt(WORD_LEN.W))
    val op2    = Input(UInt(WORD_LEN.W))
    val immsb  = Input(UInt(WORD_LEN.W))
    val exsel  = Input(UInt(EX_SEL_LEN.W))
    val aluout = Output(UInt(WORD_LEN.W))
    val bren   = Output(Bool())
    val braddr = Output(UInt(WORD_LEN.W))
  })
  // -------- ALU --------
  io.aluout := MuxCase(0.U(WORD_LEN.W), Seq(
    (io.exsel === EX_ADD)  -> (io.op1 + io.op2),
    (io.exsel === EX_SUB)  -> (io.op1 - io.op2),
    (io.exsel === EX_AND)  -> (io.op1 & io.op2),
    (io.exsel === EX_OR)   -> (io.op1 | io.op2),
    (io.exsel === EX_XOR)  -> (io.op1 ^ io.op2),
    (io.exsel === EX_SLL)  -> (io.op1 << io.op2(4,0)),
    (io.exsel === EX_SRL)  -> (io.op1 >> io.op2(4,0)),
    (io.exsel === EX_SRA)  -> (io.op1.asSInt >> io.op2(4,0)).asUInt,
    (io.exsel === EX_SLT)  -> (io.op1.asSInt < io.op2.asSInt).asUInt,
    (io.exsel === EX_SLTU) -> (io.op1 < io.op2),
  ))
  // -------- Branch --------
  io.bren := MuxCase(false.B, Seq(
    (io.exsel === EX_JAL)  ->  1.U,
    (io.exsel === EX_BEQ)  ->  (io.op1 === io.op2),
    (io.exsel === EX_BNE)  -> !(io.op1 === io.op2),
    (io.exsel === EX_BLT)  ->  (io.op1.asSInt < io.op2.asSInt),
    (io.exsel === EX_BGE)  -> !(io.op1.asSInt < io.op2.asSInt),
    (io.exsel === EX_BLTU) ->  (io.op1 < io.op2),
    (io.exsel === EX_BGEU) -> !(io.op1 < io.op2),
  ))
  io.braddr := Mux(io.exsel === EX_JAL,
    io.op1 + io.op2, io.pc + io.immsb)
}

// ---------------------------
// Riscv32E CPU（单周期）
// ---------------------------
class Riscv32E extends Module {
  import Riscv32E_Instructions._
  import Riscv32E_Parameters._
  val io = IO(new Bundle {
    val pc   = Output(UInt(WORD_LEN.W))
    val inst = Input(UInt(WORD_LEN.W))

    val mem_re    = Output(Bool())
    val mem_we    = Output(Bool())
    val mem_len   = Output(UInt(4.W))
    val mem_addr  = Output(UInt(WORD_LEN.W))
    val mem_wdata = Output(UInt(WORD_LEN.W))
    val mem_rdata = Input(UInt(WORD_LEN.W))
  })

  val ifStage = Module(new Riscv32E_IF)
  val idStage = Module(new Riscv32E_ID)
  val exStage = Module(new Riscv32E_EX)

  // IF
  io.pc := ifStage.io.pc
  ifStage.io.bren   := exStage.io.bren
  ifStage.io.braddr := exStage.io.braddr
  ifStage.io.halt   := idStage.io.halt

  // ID
  idStage.io.pc   := ifStage.io.pc
  idStage.io.inst := io.inst

  // EX
  exStage.io.pc    := idStage.io.pc
  exStage.io.op1   := idStage.io.op1
  exStage.io.op2   := idStage.io.op2
  exStage.io.immsb := idStage.io.immsb
  exStage.io.exsel := idStage.io.exsel

  // Memory
  io.mem_re    := idStage.io.memRen
  io.mem_we    := idStage.io.memWen
  io.mem_addr  := exStage.io.aluout
  io.mem_wdata := idStage.io.rs2
  io.mem_len   := Mux(idStage.io.memBen, 1.U, 4.U)

  // Write Back
  val wb_data  = Mux(
    idStage.io.memRen, io.mem_rdata, exStage.io.aluout
  )

  idStage.io.wb_en   := idStage.io.regWen
  idStage.io.wb_rd   := idStage.io.rd_addr
  idStage.io.wb_data := wb_data

  // DiffTest
  val difftest = Module(new DiffTest)
  difftest.io.clk  := clock
  difftest.io.pc   := ifStage.io.pc
  difftest.io.npc  := Mux(exStage.io.bren, exStage.io.braddr, ifStage.io.npc)
  difftest.io.inst := idStage.io.inst
  for (i <- 0 until 32) {
    difftest.io.gpr(i) := idStage.io.gprOut(i)
  }
  for (i <- 0 until 4) {
    difftest.io.csr(i) := idStage.io.csrOut(i)
  }
}

// ---------------------------
// Riscv32E TOP：自包含 CPU + ROM + RAM
// ---------------------------
class Riscv32ETOP extends Module {
  val cpu = Module(new Riscv32E)
  val rom = Module(new ROM_DPI)
  val ram = Module(new RAM_DPI)

  // 指令取值
  rom.io.addr := cpu.io.pc
  cpu.io.inst := rom.io.data

  // 数据访存
  ram.io.re    := cpu.io.mem_re
  ram.io.we    := cpu.io.mem_we
  ram.io.len   := cpu.io.mem_len
  ram.io.addr  := cpu.io.mem_addr
  ram.io.wdata := cpu.io.mem_wdata
  cpu.io.mem_rdata := ram.io.rdata
}
