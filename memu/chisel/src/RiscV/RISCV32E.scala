package riscv

import chisel3._
import chisel3.util._
import Instructions._
import Constants._
import Constants.Riscv32E._

// ---------------------------
// IF 模块：Instruction Fetch
// ---------------------------
class Riscv32E_IF extends Module {
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
  val io = IO(new Bundle {
    val pc      = Input(UInt(WORD_LEN.W))
    val inst    = Input(UInt(WORD_LEN.W))

    // 写回
    val wb_en   = Input(Bool())
    val wb_rd   = Input(UInt(5.W))
    val memData = Input(UInt(WORD_LEN.W))
    val exData  = Input(UInt(WORD_LEN.W))

    // 输出到 EX
    val exsel   = Output(EX())
    val op1     = Output(UInt(WORD_LEN.W))
    val op2     = Output(UInt(WORD_LEN.W))
    val immsb   = Output(UInt(WORD_LEN.W))
    val rs2     = Output(UInt(WORD_LEN.W))
    val rd_addr = Output(UInt(5.W))

    // Control signals
    val halt   = Output(Bool())
    val memsel = Output(MEM())
    val regWen = Output(Bool())

    // Diff
    val csrOut = Output(Vec(CSR_NUM, UInt(WORD_LEN.W)))
    val gprOut = Output(Vec(GPR_NUM, UInt(WORD_LEN.W)))
  })

  val List(op1sel, op2sel, exsel, wbsel, memsel, csrsel) = ListLookup(io.inst,
    List(OP1.RS1, OP2.RS2, EX.ADD, WB.EX, MEM.NONE, CSRS.NONE), Array(
      LW     -> List(OP1.RS1 , OP2.IMI , EX.ADD , WB.MEM , MEM.RW  , CSRS.NONE),  // x[rs1] + sext(immi)
      LH     -> List(OP1.RS1 , OP2.IMI , EX.ADD , WB.MEM , MEM.RH  , CSRS.NONE),  // x[rs1] + sext(immi)
      LB     -> List(OP1.RS1 , OP2.IMI , EX.ADD , WB.MEM , MEM.RB  , CSRS.NONE),  // x[rs1] + sext(immi)
      LHU    -> List(OP1.RS1 , OP2.IMI , EX.ADD , WB.MEM , MEM.RHU , CSRS.NONE),  // x[rs1] + sext(immi)
      LBU    -> List(OP1.RS1 , OP2.IMI , EX.ADD , WB.MEM , MEM.RBU , CSRS.NONE),  // x[rs1] + sext(immi)
      SW     -> List(OP1.RS1 , OP2.IMS , EX.ADD , WB.NONE, MEM.WW  , CSRS.NONE),  // x[rs1] + sext(imms)
      SH     -> List(OP1.RS1 , OP2.IMS , EX.ADD , WB.NONE, MEM.WH  , CSRS.NONE),  // x[rs1] + sext(imms)
      SB     -> List(OP1.RS1 , OP2.IMS , EX.ADD , WB.NONE, MEM.WB  , CSRS.NONE),  // x[rs1] + sext(imms)

      ADD    -> List(OP1.RS1 , OP2.RS2 , EX.ADD , WB.EX  , MEM.NONE, CSRS.NONE),  // x[rs1] + x[rs2]
      ADDI   -> List(OP1.RS1 , OP2.IMI , EX.ADD , WB.EX  , MEM.NONE, CSRS.NONE),  // x[rs1] + sext(immi)
      SUB    -> List(OP1.RS1 , OP2.RS2 , EX.SUB , WB.EX  , MEM.NONE, CSRS.NONE),  // x[rs1] - x[rs2]
      AND    -> List(OP1.RS1 , OP2.RS2 , EX.AND , WB.EX  , MEM.NONE, CSRS.NONE),  // x[rs1] & x[rs2]
      OR     -> List(OP1.RS1 , OP2.RS2 , EX.OR  , WB.EX  , MEM.NONE, CSRS.NONE),  // x[rs1] | x[rs2]
      XOR    -> List(OP1.RS1 , OP2.RS2 , EX.XOR , WB.EX  , MEM.NONE, CSRS.NONE),  // x[rs1] ^ x[rs2]
      ANDI   -> List(OP1.RS1 , OP2.IMI , EX.AND , WB.EX  , MEM.NONE, CSRS.NONE),  // x[rs1] & sext(immi)
      ORI    -> List(OP1.RS1 , OP2.IMI , EX.OR  , WB.EX  , MEM.NONE, CSRS.NONE),  // x[rs1] | sext(immi)
      XORI   -> List(OP1.RS1 , OP2.IMI , EX.XOR , WB.EX  , MEM.NONE, CSRS.NONE),  // x[rs1] ^ sext(immi)
      SLL    -> List(OP1.RS1 , OP2.RS2 , EX.SLL , WB.EX  , MEM.NONE, CSRS.NONE),  // x[rs1] << x[rs2](4,0)
      SRL    -> List(OP1.RS1 , OP2.RS2 , EX.SRL , WB.EX  , MEM.NONE, CSRS.NONE),  // x[rs1] >>u x[rs2](4,0)
      SRA    -> List(OP1.RS1 , OP2.RS2 , EX.SRA , WB.EX  , MEM.NONE, CSRS.NONE),  // x[rs1] >>s x[rs2](4,0)
      SLLI   -> List(OP1.RS1 , OP2.IMI , EX.SLL , WB.EX  , MEM.NONE, CSRS.NONE),  // x[rs1] << immsi(4,0)
      SRLI   -> List(OP1.RS1 , OP2.IMI , EX.SRL , WB.EX  , MEM.NONE, CSRS.NONE),  // x[rs1] >>u immsi(4,0)
      SRAI   -> List(OP1.RS1 , OP2.IMI , EX.SRA , WB.EX  , MEM.NONE, CSRS.NONE),  // x[rs1] >>s immsi(4,0)
      SLT    -> List(OP1.RS1 , OP2.RS2 , EX.SLT , WB.EX  , MEM.NONE, CSRS.NONE),  // x[rs1] <s x[rs2]
      SLTU   -> List(OP1.RS1 , OP2.RS2 , EX.SLTU, WB.EX  , MEM.NONE, CSRS.NONE),  // x[rs1] <u x[rs2]
      SLTI   -> List(OP1.RS1 , OP2.IMI , EX.SLT , WB.EX  , MEM.NONE, CSRS.NONE),  // x[rs1] <s immsi
      SLTIU  -> List(OP1.RS1 , OP2.IMI , EX.SLTU, WB.EX  , MEM.NONE, CSRS.NONE),  // x[rs1] <u immsi

      BEQ    -> List(OP1.RS1 , OP2.RS2 , EX.BEQ , WB.NONE, MEM.NONE, CSRS.NONE),  // x[rs1] === x[rs2] then PC+sext(imm_b)
      BNE    -> List(OP1.RS1 , OP2.RS2 , EX.BNE , WB.NONE, MEM.NONE, CSRS.NONE),  // x[rs1] =/= x[rs2] then PC+sext(imm_b)
      BGE    -> List(OP1.RS1 , OP2.RS2 , EX.BGE , WB.NONE, MEM.NONE, CSRS.NONE),  // x[rs1] >=s x[rs2] then PC+sext(imm_b)
      BGEU   -> List(OP1.RS1 , OP2.RS2 , EX.BGEU, WB.NONE, MEM.NONE, CSRS.NONE),  // x[rs1] >=u x[rs2] then PC+sext(imm_b)
      BLT    -> List(OP1.RS1 , OP2.RS2 , EX.BLT , WB.NONE, MEM.NONE, CSRS.NONE),  // x[rs1] <s x[rs2]  then PC+sext(imm_b)
      BLTU   -> List(OP1.RS1 , OP2.RS2 , EX.BLTU, WB.NONE, MEM.NONE, CSRS.NONE),  // x[rs1] <u x[rs2]  then PC+sext(imm_b)
      JAL    -> List(OP1.PC  , OP2.IMJ , EX.JAL , WB.PC  , MEM.NONE, CSRS.NONE),  // x[rd] <- PC+4 and PC+sext(imm_j)
      JALR   -> List(OP1.RS1 , OP2.IMI , EX.JAL , WB.PC  , MEM.NONE, CSRS.NONE),  // x[rd] <- PC+4 and (x[rs1]+sext(imm_i))&~1

      LUI    -> List(OP1.NONE, OP2.IMU , EX.ADD , WB.EX  , MEM.NONE, CSRS.NONE),  // sext(immu[31:12] << 12)
      AUIPC  -> List(OP1.PC  , OP2.IMU , EX.ADD , WB.EX  , MEM.NONE, CSRS.NONE),  // PC + sext(immu[31:12] << 12)

      CSRRW  -> List(OP1.RS1 , OP2.NONE, EX.ADD , WB.CSR , MEM.NONE, CSRS.W   ), // CSRs[csr] <- x[rs1]
      CSRRWI -> List(OP1.IMZ , OP2.NONE, EX.ADD , WB.CSR , MEM.NONE, CSRS.W   ), // CSRs[csr] <- uext(imm_z)
      CSRRS  -> List(OP1.RS1 , OP2.NONE, EX.ADD , WB.CSR , MEM.NONE, CSRS.S   ), // CSRs[csr] <- CSRs[csr] | x[rs1]
      CSRRSI -> List(OP1.IMZ , OP2.NONE, EX.ADD , WB.CSR , MEM.NONE, CSRS.S   ), // CSRs[csr] <- CSRs[csr] | uext(imm_z)
      CSRRC  -> List(OP1.RS1 , OP2.NONE, EX.ADD , WB.CSR , MEM.NONE, CSRS.C   ), // CSRs[csr] <- CSRs[csr]&~x[rs1]
      CSRRCI -> List(OP1.IMZ , OP2.NONE, EX.ADD , WB.CSR , MEM.NONE, CSRS.C   ), // CSRs[csr] <- CSRs[csr]&~uext(imm_z)

      EBREAK -> List(OP1.NONE, OP2.NONE, EX.NONE, WB.NONE, MEM.NONE, CSRS.B   ),
      ECALL  -> List(OP1.NONE, OP2.CSR , EX.CSR , WB.NONE, MEM.NONE, CSRS.E   ),
      MRET   -> List(OP1.NONE, OP2.CSR , EX.CSR , WB.NONE, MEM.NONE, CSRS.MRET),
    ),
  )

  // -------- 寄存器堆 --------
  val CSR = RegInit(VecInit(Seq.fill(CSR_NUM)(0.U(WORD_LEN.W))))
  val GPR = RegInit(VecInit(Seq.fill(GPR_NUM)(0.U(WORD_LEN.W))))

  // -------- 指令字段 --------
  val rd  = io.inst(11,7)
  val rs1 = io.inst(19,15)
  val rs2 = io.inst(24,20)

  // -------- 立即数 --------
  // sext 12bit value to 32bit value.
  val immi = io.inst(31,20)  // imm for I-type
  val immsi = Cat(Fill(20, immi(11)), immi)
  val imms = Cat(io.inst(31,25), io.inst(11,7))  // imm for S-type
  val immss = Cat(Fill(20, imms(11)), imms)
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
  val immuz = Cat(Fill(27, 0.U), immz)  // for CSRS instructions

  // -------- EX功能 --------
  io.exsel := exsel
  io.immsb := immsb
  io.rs2 := GPR(rs2)
  // Determine 1st operand data signal
  io.op1 := MuxCase(0.U(32.W), Seq(
    (op1sel === OP1.RS1) -> GPR(rs1),
    (op1sel === OP1.PC ) -> io.pc,
    (op1sel === OP1.IMZ) -> immuz,
  ))
  // Determine 2nd operand data signal
  val brcsr = MuxCase(0.U(32.W), Seq(
    (csrsel === CSRS.E   ) -> CSR(3),  // mtvec
    (csrsel === CSRS.MRET) -> CSR(1),  // mepc
  ))
  io.op2 := MuxCase(0.U(32.W), Seq(
    (op2sel === OP2.RS2) -> GPR(rs2),
    (op2sel === OP2.CSR) -> brcsr,
    (op2sel === OP2.IMI) -> immsi,
    (op2sel === OP2.IMS) -> immss,
    (op2sel === OP2.IMJ) -> immsj,
    (op2sel === OP2.IMU) -> immu,  // for LUI and AUIPC
  ))

  // -------- WB功能 --------
  io.memsel := memsel
  // CSR
  val CSR_MSTATUS = 0.U
  val CSR_MEPC    = 1.U
  val CSR_MCAUSE  = 2.U
  val CSR_MTVEC   = 3.U
  val CSR_MCYCLE  = 4.U
  val CSR_MCYCLEH = 5.U
  val CSR_MVENDOR = 6.U
  val CSR_MARCHID = 7.U
  val csr_addr = immi
  val csr_id = MuxLookup(csr_addr, 0.U)(Seq(
    0x300.U -> 0.U,  // mstatus
    0x341.U -> 1.U,  // mepc
    0x342.U -> 2.U,  // mcause
    0x305.U -> 3.U,  // mtvec
    0xB00.U -> 4.U,  // mcycle
    0xB80.U -> 5.U,  // mcycleh
    0xF11.U -> 6.U,  // mvendorid
    0xF12.U -> 7.U,  // marchid
  ))
  val cycle64 = Cat(CSR(CSR_MCYCLEH), CSR(CSR_MCYCLE)) + 1.U
  CSR(CSR_MCYCLE)  := cycle64(31,0)
  CSR(CSR_MCYCLEH) := cycle64(63,32)
  CSR(CSR_MVENDOR) := 0x79737978.U  // ysyx
  CSR(CSR_MARCHID) := 0x018CE26E.U  // moongrt - 26010030

  val csr_old = CSR(csr_id)
  val csr_new = MuxCase(io.op1, Seq(
    (csrsel === CSRS.W) -> io.op1,
    (csrsel === CSRS.S) -> (csr_old | io.op1),
    (csrsel === CSRS.C) -> (csr_old & ~io.op1),
  ))
  val csr_wen = csrsel.isOneOf(CSRS.W, CSRS.S, CSRS.C)
  val csr_writable =
    csr_id === CSR_MSTATUS || csr_id === CSR_MEPC || csr_id === CSR_MCAUSE ||
    csr_id === CSR_MTVEC || csr_id === CSR_MCYCLE || csr_id === CSR_MCYCLEH
  when (~reset.asBool && csr_wen && csr_writable) {
    CSR(csr_id) := csr_new
  }
  when (~reset.asBool && csrsel === CSRS.E) {
    // mstatus = 0x00001800
    CSR(CSR_MSTATUS) := 0x00001800.U
    // mepc = pc
    CSR(CSR_MEPC)    := io.pc
    // mcause = 11 (ECALL from M-mode)
    CSR(CSR_MCAUSE)  := 11.U
  }
  when (~reset.asBool && csrsel === CSRS.MRET) {
    // mstatus = 0x00000080
    CSR(CSR_MSTATUS) := 0x00000080.U
  }
  // GPR
  io.rd_addr := rd
  io.regWen  := wbsel =/= WB.NONE
  val memData = MuxLookup(io.memsel, 0.U(WORD_LEN.W))(Seq(
    MEM.RW  -> io.memData,  // LW 直接写回
    MEM.RB  -> Cat(Fill(24, io.memData(7)), io.memData(7,0)),  // LB 符号扩展
    MEM.RH  -> Cat(Fill(16, io.memData(15)), io.memData(15,0)),  // LH 符号扩展
    MEM.RBU -> Cat(0.U(24.W), io.memData(7,0)),  // LBU 零扩展
    MEM.RHU -> Cat(0.U(16.W), io.memData(15,0)),  // LHU 零扩展
  ))
  when (io.wb_en && io.wb_rd =/= 0.U) {
    GPR(io.wb_rd) := MuxCase(0.U, Seq(
      (wbsel === WB.PC ) -> (io.pc + 4.U),
      (wbsel === WB.EX ) -> io.exData,
      (wbsel === WB.MEM) -> memData,
      (wbsel === WB.CSR) -> csr_old,
    ))
  }

  // 输出 CSRS & GPR
  io.csrOut := CSR
  io.gprOut := GPR

  // -------- 异常处理 --------
  val trap = Module(new EBreak)
  // 定义异常编码规则
  // 0: EBREAK, 1: 全零指令, 2: 其他E指令, 3: 未实现指令
  val impl_inst = Riscv32E_IMPLED.filterNot(inst =>
    inst == E || inst == EBREAK
  )
  val is_unimpl = ~impl_inst.map(inst => io.inst === inst).reduce(_ || _)
  val is_zero = (io.inst === 0.U)
  val is_ebreak = (io.inst === EBREAK)
  val is_otherE = (io.inst === E) && (io.inst =/= ECALL) && (io.inst =/= EBREAK)
  val exc_code = MuxCase(1.U(8.W), Seq(  // 默认全零指令
      is_ebreak -> 0.U,  // EBREAK
      is_zero   -> 1.U,  // 全零指令
      is_otherE -> 2.U,  // 其他E指令
      is_unimpl -> 3.U,  // 未实现指令
    )
  )
  // 输出到 EBreak 模块
  trap.io.clk  := clock
  trap.io.trap := ~reset.asBool && is_unimpl
  trap.io.code := exc_code
  // halt 信号
  io.halt := ~reset.asBool && is_unimpl
}

// ---------------------------
// EX 模块
// ---------------------------
class Riscv32E_EX extends Module {
  val io = IO(new Bundle {
    val pc     = Input(UInt(WORD_LEN.W))
    val op1    = Input(UInt(WORD_LEN.W))
    val op2    = Input(UInt(WORD_LEN.W))
    val immsb  = Input(UInt(WORD_LEN.W))
    val exsel  = Input(EX())
    val aluout = Output(UInt(WORD_LEN.W))
    val bren   = Output(Bool())
    val braddr = Output(UInt(WORD_LEN.W))
  })
  // -------- ALU --------
  io.aluout := MuxCase(0.U(WORD_LEN.W), Seq(
    (io.exsel === EX.ADD ) -> (io.op1 + io.op2),
    (io.exsel === EX.SUB ) -> (io.op1 - io.op2),
    (io.exsel === EX.AND ) -> (io.op1 & io.op2),
    (io.exsel === EX.OR  ) -> (io.op1 | io.op2),
    (io.exsel === EX.XOR ) -> (io.op1 ^ io.op2),
    (io.exsel === EX.SLL ) -> (io.op1 << io.op2(4,0)),
    (io.exsel === EX.SRL ) -> (io.op1 >> io.op2(4,0)),
    (io.exsel === EX.SRA ) -> (io.op1.asSInt >> io.op2(4,0)).asUInt,
    (io.exsel === EX.SLT ) -> (io.op1.asSInt < io.op2.asSInt).asUInt,
    (io.exsel === EX.SLTU) -> (io.op1 < io.op2),
  ))
  // -------- Branch --------
  io.bren := MuxCase(false.B, Seq(
    (io.exsel === EX.JAL ) ->  true.B,
    (io.exsel === EX.CSR ) ->  true.B,
    (io.exsel === EX.BEQ ) ->  (io.op1 === io.op2),
    (io.exsel === EX.BNE ) -> !(io.op1 === io.op2),
    (io.exsel === EX.BLT ) ->  (io.op1.asSInt < io.op2.asSInt),
    (io.exsel === EX.BGE ) -> !(io.op1.asSInt < io.op2.asSInt),
    (io.exsel === EX.BLTU) ->  (io.op1 < io.op2),
    (io.exsel === EX.BGEU) -> !(io.op1 < io.op2),
  ))
  io.braddr := MuxCase(io.pc + io.immsb, Seq(
    (io.exsel === EX.JAL) -> (io.op1 + io.op2),
    (io.exsel === EX.CSR) -> (io.op2),  // mtvec
  ))
}

// ---------------------------
// Riscv32E CPU（单周期）
// ---------------------------
class Riscv32E extends Module {
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
  val isLoad  = Seq(MEM.RW, MEM.RH, MEM.RB, MEM.RHU, MEM.RBU).map(idStage.io.memsel === _).reduce(_||_) && !reset.asBool
  val isStore = Seq(MEM.WW, MEM.WH, MEM.WB).map(idStage.io.memsel === _).reduce(_||_) && !reset.asBool
  val isByte  = Seq(MEM.WB, MEM.RB, MEM.RBU).map(idStage.io.memsel === _).reduce(_||_) && !reset.asBool
  val isHalf  = Seq(MEM.WH, MEM.RH, MEM.RHU).map(idStage.io.memsel === _).reduce(_||_) && !reset.asBool
  io.mem_re    := isLoad
  io.mem_we    := isStore
  io.mem_addr  := exStage.io.aluout
  io.mem_wdata := idStage.io.rs2
  io.mem_len   := Mux(isByte, 1.U, Mux(isHalf, 2.U, 4.U))

  // Write Back
  idStage.io.wb_en   := idStage.io.regWen
  idStage.io.wb_rd   := idStage.io.rd_addr
  idStage.io.memData := io.mem_rdata
  idStage.io.exData  := exStage.io.aluout

  // DiffTest
  val difftest = Module(new DiffTest)
  difftest.io.clk  := clock
  difftest.io.pc   := ifStage.io.pc
  difftest.io.npc  := Mux(exStage.io.bren, exStage.io.braddr, ifStage.io.npc)
  difftest.io.inst := idStage.io.inst
  for (i <- 0 until CSR_NUM) {
    difftest.io.csr(i) := idStage.io.csrOut(i)
  }
  for (i <- 0 until GPR_NUM) {
    difftest.io.gpr(i) := idStage.io.gprOut(i)
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
  ram.io.clk   := clock
  ram.io.re    := cpu.io.mem_re
  ram.io.we    := cpu.io.mem_we
  ram.io.len   := cpu.io.mem_len
  ram.io.addr  := cpu.io.mem_addr
  ram.io.wdata := cpu.io.mem_wdata
  cpu.io.mem_rdata := ram.io.rdata
}
