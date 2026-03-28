package riscv.e

import chisel3._
import chisel3.util._
import riscv.Instructions._
import riscv.Constants._
import riscv.Constants.Riscv32E._
import riscv.util._

// GPR: general purpose registers
class GPRFile extends Module {
  val io = IO(new Bundle {
    // WB
    val wen   = Input(Bool())
    val waddr = Input(UInt(log2Ceil(GPR_NUM).W))
    val wdata = Input(UInt(DataWidth.W))
    // RS1/RS2
    val rs1 = Input(UInt(log2Ceil(GPR_NUM).W))
    val rs2 = Input(UInt(log2Ceil(GPR_NUM).W))
    val RS1 = Output(UInt(DataWidth.W))
    val RS2 = Output(UInt(DataWidth.W))
  })
  val GPR = RegInit(VecInit(Seq.fill(GPR_NUM)(0.U(DataWidth.W))))
  io.RS1 := GPR(io.rs1)
  io.RS2 := GPR(io.rs2)
  when (io.wen && (io.waddr =/= 0.U)) {
    GPR(io.waddr) := io.wdata
  }
  // -------- DiffTest --------
  val diffgpr = Module(new DiffGPR)
  for (i <- 0 until GPR_NUM) {
    diffgpr.io.gpr(i) := GPR(i)
  }
}

// CSR: control and status registers
class CSRFile extends Module {
  val io = IO(new Bundle {
    val csrsel = Input(CSRS())  // CSRS.W / S / C / E / MRET
    val pc     = Input(UInt(DataWidth.W))
    val addr   = Input(UInt(12.W))
    val wdata  = Input(UInt(DataWidth.W))
    val rdata  = Output(UInt(DataWidth.W))
  })
  val csr = RegInit(VecInit(Seq.fill(CSR_NUM)(0.U(DataWidth.W))))
  // CSR 索引
  val CSR_MSTATUS = 0.U
  val CSR_MEPC    = 1.U
  val CSR_MCAUSE  = 2.U
  val CSR_MTVEC   = 3.U
  val CSR_MCYCLE  = 4.U
  val CSR_MCYCLEH = 5.U
  val CSR_MVENDOR = 6.U
  val CSR_MARCH   = 7.U
  val csrid = MuxLookup(io.addr, 0.U)(Seq(
    0x300.U -> 0.U,  // mstatus
    0x341.U -> 1.U,  // mepc
    0x342.U -> 2.U,  // mcause
    0x305.U -> 3.U,  // mtvec
    0xB00.U -> 4.U,  // mcycle
    0xB80.U -> 5.U,  // mcycleh
    0xF11.U -> 6.U,  // mvendorid
    0xF12.U -> 7.U,  // marchid
  ))
  // cycle
  val cycle64 = Cat(csr(CSR_MCYCLEH), csr(CSR_MCYCLE)) + 1.U
  csr(CSR_MCYCLE)  := cycle64(31,0)
  csr(CSR_MCYCLEH) := cycle64(63,32)
  // Read
  io.rdata := MuxCase(csr(csrid), Seq(
    (io.csrsel === CSRS.E   ) -> csr(CSR_MTVEC),  // mtvec
    (io.csrsel === CSRS.MRET) -> csr(CSR_MEPC),   // mepc
  ))
  // Write
  val csr_wen = io.csrsel.isOneOf(CSRS.W, CSRS.S, CSRS.C)
  when (csr_wen) {
    csr(csrid) := MuxCase(io.wdata, Seq(
      (io.csrsel === CSRS.W) -> io.wdata,
      (io.csrsel === CSRS.S) -> (csr(csrid) | io.wdata),
      (io.csrsel === CSRS.C) -> (csr(csrid) & ~io.wdata),
    ))
  }
  // ECALL
  when (io.csrsel === CSRS.E) {
    csr(CSR_MSTATUS) := 0x00001800.U
    csr(CSR_MEPC)    := io.pc
    csr(CSR_MCAUSE)  := 11.U
  }
  // MRET
  when (io.csrsel === CSRS.MRET) {
    csr(CSR_MSTATUS) := 0x00000080.U
  }
  // -------- DiffTest --------
  val diffcsr = Module(new DiffCSR)
  for (i <- 0 until CSR_NUM) {
    diffcsr.io.csr(i) := csr(i)
  }
}

// ----------------------------------
// IDU 模块：Instruction Decode Unit
// ----------------------------------
class IDU extends Module {
  val io = IO(new Bundle {
    val pc      = Input(UInt(DataWidth.W))
    val npc     = Input(UInt(DataWidth.W))
    val inst    = Input(UInt(DataWidth.W))
    // EXU
    val exsel = Output(EX())
    val op1   = Output(UInt(DataWidth.W))
    val op2   = Output(UInt(DataWidth.W))
    val RS2   = Output(UInt(DataWidth.W))
    val immsb = Output(UInt(DataWidth.W))
    // LSU
    val memsel = Output(MEM())
    // WBU
    val wben    = Input(Bool())
    val wbAddr  = Input(UInt(log2Ceil(GPR_NUM).W))
    val wbData  = Input(UInt(DataWidth.W))
    val wbsel   = Output(WB())
    val wbrd    = Output(UInt(log2Ceil(GPR_NUM).W))
    // Ctrl
    val halt   = Output(Bool())
  })

  val List(op1sel, op2sel, csrsel, exsel, memsel, wbsel) = ListLookup(io.inst,
    List(OP1.RS1, OP2.RS2, CSRS.NONE, EX.ADD, MEM.NONE, WB.EX), Array(
      // Load/Store
      LW     -> List(OP1.RS1 , OP2.IMI , CSRS.NONE, EX.ADD , MEM.RW  , WB.MEM ),  // x[rs1] + sext(immi)
      LH     -> List(OP1.RS1 , OP2.IMI , CSRS.NONE, EX.ADD , MEM.RH  , WB.MEM ),  // x[rs1] + sext(immi)
      LB     -> List(OP1.RS1 , OP2.IMI , CSRS.NONE, EX.ADD , MEM.RB  , WB.MEM ),  // x[rs1] + sext(immi)
      LHU    -> List(OP1.RS1 , OP2.IMI , CSRS.NONE, EX.ADD , MEM.RHU , WB.MEM ),  // x[rs1] + sext(immi)
      LBU    -> List(OP1.RS1 , OP2.IMI , CSRS.NONE, EX.ADD , MEM.RBU , WB.MEM ),  // x[rs1] + sext(immi)
      SW     -> List(OP1.RS1 , OP2.IMS , CSRS.NONE, EX.ADD , MEM.WW  , WB.NONE),  // x[rs1] + sext(imms)
      SH     -> List(OP1.RS1 , OP2.IMS , CSRS.NONE, EX.ADD , MEM.WH  , WB.NONE),  // x[rs1] + sext(imms)
      SB     -> List(OP1.RS1 , OP2.IMS , CSRS.NONE, EX.ADD , MEM.WB  , WB.NONE),  // x[rs1] + sext(imms)
      LUI    -> List(OP1.NONE, OP2.IMU , CSRS.NONE, EX.ADD , MEM.NONE, WB.EX  ),  // sext(immu[31:12] << 12)
      AUIPC  -> List(OP1.PC  , OP2.IMU , CSRS.NONE, EX.ADD , MEM.NONE, WB.EX  ),  // PC + sext(immu[31:12] << 12)
      // Arithmetic
      ADD    -> List(OP1.RS1 , OP2.RS2 , CSRS.NONE, EX.ADD , MEM.NONE, WB.EX  ),  // x[rs1] + x[rs2]
      ADDI   -> List(OP1.RS1 , OP2.IMI , CSRS.NONE, EX.ADD , MEM.NONE, WB.EX  ),  // x[rs1] + sext(immi)
      SUB    -> List(OP1.RS1 , OP2.RS2 , CSRS.NONE, EX.SUB , MEM.NONE, WB.EX  ),  // x[rs1] - x[rs2]
      AND    -> List(OP1.RS1 , OP2.RS2 , CSRS.NONE, EX.AND , MEM.NONE, WB.EX  ),  // x[rs1] & x[rs2]
      OR     -> List(OP1.RS1 , OP2.RS2 , CSRS.NONE, EX.OR  , MEM.NONE, WB.EX  ),  // x[rs1] | x[rs2]
      XOR    -> List(OP1.RS1 , OP2.RS2 , CSRS.NONE, EX.XOR , MEM.NONE, WB.EX  ),  // x[rs1] ^ x[rs2]
      ANDI   -> List(OP1.RS1 , OP2.IMI , CSRS.NONE, EX.AND , MEM.NONE, WB.EX  ),  // x[rs1] & sext(immi)
      ORI    -> List(OP1.RS1 , OP2.IMI , CSRS.NONE, EX.OR  , MEM.NONE, WB.EX  ),  // x[rs1] | sext(immi)
      XORI   -> List(OP1.RS1 , OP2.IMI , CSRS.NONE, EX.XOR , MEM.NONE, WB.EX  ),  // x[rs1] ^ sext(immi)
      SLL    -> List(OP1.RS1 , OP2.RS2 , CSRS.NONE, EX.SLL , MEM.NONE, WB.EX  ),  // x[rs1] << x[rs2](4,0)
      SRL    -> List(OP1.RS1 , OP2.RS2 , CSRS.NONE, EX.SRL , MEM.NONE, WB.EX  ),  // x[rs1] >>u x[rs2](4,0)
      SRA    -> List(OP1.RS1 , OP2.RS2 , CSRS.NONE, EX.SRA , MEM.NONE, WB.EX  ),  // x[rs1] >>s x[rs2](4,0)
      SLLI   -> List(OP1.RS1 , OP2.IMI , CSRS.NONE, EX.SLL , MEM.NONE, WB.EX  ),  // x[rs1] << immsi(4,0)
      SRLI   -> List(OP1.RS1 , OP2.IMI , CSRS.NONE, EX.SRL , MEM.NONE, WB.EX  ),  // x[rs1] >>u immsi(4,0)
      SRAI   -> List(OP1.RS1 , OP2.IMI , CSRS.NONE, EX.SRA , MEM.NONE, WB.EX  ),  // x[rs1] >>s immsi(4,0)
      SLT    -> List(OP1.RS1 , OP2.RS2 , CSRS.NONE, EX.SLT , MEM.NONE, WB.EX  ),  // x[rs1] <s x[rs2]
      SLTU   -> List(OP1.RS1 , OP2.RS2 , CSRS.NONE, EX.SLTU, MEM.NONE, WB.EX  ),  // x[rs1] <u x[rs2]
      SLTI   -> List(OP1.RS1 , OP2.IMI , CSRS.NONE, EX.SLT , MEM.NONE, WB.EX  ),  // x[rs1] <s immsi
      SLTIU  -> List(OP1.RS1 , OP2.IMI , CSRS.NONE, EX.SLTU, MEM.NONE, WB.EX  ),  // x[rs1] <u immsi
      // Branch
      BEQ    -> List(OP1.RS1 , OP2.RS2 , CSRS.NONE, EX.BEQ , MEM.NONE, WB.NONE),  // x[rs1] === x[rs2] then PC+sext(imm_b)
      BNE    -> List(OP1.RS1 , OP2.RS2 , CSRS.NONE, EX.BNE , MEM.NONE, WB.NONE),  // x[rs1] =/= x[rs2] then PC+sext(imm_b)
      BGE    -> List(OP1.RS1 , OP2.RS2 , CSRS.NONE, EX.BGE , MEM.NONE, WB.NONE),  // x[rs1] >=s x[rs2] then PC+sext(imm_b)
      BGEU   -> List(OP1.RS1 , OP2.RS2 , CSRS.NONE, EX.BGEU, MEM.NONE, WB.NONE),  // x[rs1] >=u x[rs2] then PC+sext(imm_b)
      BLT    -> List(OP1.RS1 , OP2.RS2 , CSRS.NONE, EX.BLT , MEM.NONE, WB.NONE),  // x[rs1] <s x[rs2]  then PC+sext(imm_b)
      BLTU   -> List(OP1.RS1 , OP2.RS2 , CSRS.NONE, EX.BLTU, MEM.NONE, WB.NONE),  // x[rs1] <u x[rs2]  then PC+sext(imm_b)
      JAL    -> List(OP1.PC  , OP2.IMJ , CSRS.NONE, EX.JAL , MEM.NONE, WB.PC  ),  // x[rd] <- PC+4 and PC+sext(imm_j)
      JALR   -> List(OP1.RS1 , OP2.IMI , CSRS.NONE, EX.JAL , MEM.NONE, WB.PC  ),  // x[rd] <- PC+4 and (x[rs1]+sext(imm_i))&~1
      // CSR
      CSRRW  -> List(OP1.RS1 , OP2.CSR , CSRS.W   , EX.ADD , MEM.NONE, WB.CSR ),  // CSRs[csr] <- x[rs1]
      CSRRWI -> List(OP1.IMZ , OP2.CSR , CSRS.W   , EX.ADD , MEM.NONE, WB.CSR ),  // CSRs[csr] <- uext(imm_z)
      CSRRS  -> List(OP1.RS1 , OP2.CSR , CSRS.S   , EX.ADD , MEM.NONE, WB.CSR ),  // CSRs[csr] <- CSRs[csr] | x[rs1]
      CSRRSI -> List(OP1.IMZ , OP2.CSR , CSRS.S   , EX.ADD , MEM.NONE, WB.CSR ),  // CSRs[csr] <- CSRs[csr] | uext(imm_z)
      CSRRC  -> List(OP1.RS1 , OP2.CSR , CSRS.C   , EX.ADD , MEM.NONE, WB.CSR ),  // CSRs[csr] <- CSRs[csr]&~x[rs1]
      CSRRCI -> List(OP1.IMZ , OP2.CSR , CSRS.C   , EX.ADD , MEM.NONE, WB.CSR ),  // CSRs[csr] <- CSRs[csr]&~uext(imm_z)
      // Exception
      EBREAK -> List(OP1.NONE, OP2.NONE, CSRS.B   , EX.NONE, MEM.NONE, WB.NONE),
      ECALL  -> List(OP1.NONE, OP2.CSR , CSRS.E   , EX.CSR , MEM.NONE, WB.NONE),
      MRET   -> List(OP1.NONE, OP2.CSR , CSRS.MRET, EX.CSR , MEM.NONE, WB.NONE),
    ),
  )

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

  // -------- 寄存器堆 --------
  val csr = Module(new CSRFile)
  csr.io.csrsel := csrsel
  csr.io.pc     := io.pc
  csr.io.addr   := immi
  csr.io.wdata  := io.op1
  val gpr = Module(new GPRFile)
  gpr.io.wen   := io.wben
  gpr.io.waddr := io.wbAddr
  gpr.io.wdata := io.wbData
  gpr.io.rs1   := rs1
  gpr.io.rs2   := rs2

  // -------- EX功能 --------
  io.exsel := exsel
  io.immsb := immsb
  io.RS2   := gpr.io.RS2
  // Determine 1st operand data signal
  io.op1 := MuxCase(0.U, Seq(
    (op1sel === OP1.RS1) -> gpr.io.RS1,
    (op1sel === OP1.PC ) -> io.pc,
    (op1sel === OP1.IMZ) -> immuz,
  ))
  // Determine 2nd operand data signal
  io.op2 := MuxCase(0.U, Seq(
    (op2sel === OP2.RS2) -> gpr.io.RS2,
    (op2sel === OP2.CSR) -> csr.io.rdata,
    (op2sel === OP2.IMI) -> immsi,
    (op2sel === OP2.IMS) -> immss,
    (op2sel === OP2.IMJ) -> immsj,
    (op2sel === OP2.IMU) -> immu,  // for LUI and AUIPC
  ))

  // -------- MEM功能 --------
  io.memsel := memsel

  // -------- WB功能 --------
  // GPR
  io.wbsel := wbsel
  io.wbrd  := rd

  // -------- Trap --------
  val trap = Module(new Trap(Riscv32E_IMPLED))
  trap.io.inst := io.inst
  io.halt := trap.io.halt

  // -------- DiffTest --------
  val diffpc = Module(new DiffPC)
  diffpc.io.pc   := io.pc
  diffpc.io.npc  := io.npc
  diffpc.io.inst := io.inst
}
