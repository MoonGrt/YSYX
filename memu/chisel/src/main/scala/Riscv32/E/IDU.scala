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
    // GPR
    val wen   = Input(Bool())
    val waddr = Input(UInt(log2Ceil(GPRNum).W))
    val wdata = Input(UInt(DataWidth.W))
    // RS1/RS2
    val rs1 = Input(UInt(log2Ceil(GPRNum).W))
    val rs2 = Input(UInt(log2Ceil(GPRNum).W))
    val RS1 = Output(UInt(DataWidth.W))
    val RS2 = Output(UInt(DataWidth.W))
  })
  val gpr = RegInit(VecInit(Seq.fill(GPRNum)(0.U(DataWidth.W))))
  io.RS1 := gpr(io.rs1)
  io.RS2 := gpr(io.rs2)
  when (io.wen && (io.waddr =/= 0.U)) {
    gpr(io.waddr) := io.wdata
  }
  // -----------------------------------------------
  // -------------------- DiffTest -----------------
  // -----------------------------------------------
  val diffgpr = Module(new DiffGPR)
  for (i <- 0 until GPRNum) {
    diffgpr.io.gpr(i) := gpr(i)
  }
}

// CSR: control and status registers
class CSRFile extends Module {
  val io = IO(new Bundle {
    val csrSel = Input(CSR())
    val pc     = Input(UInt(DataWidth.W))
    val addr   = Input(UInt(CSRWidth.W))
    val wdata  = Input(UInt(DataWidth.W))
    val rdata  = Output(UInt(DataWidth.W))
  })
  val csr = RegInit(VecInit(Seq.fill(CSRNum)(0.U(DataWidth.W))))
  // CSR Index
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
  csr(CSR_MCYCLE ) := cycle64(31,0)
  csr(CSR_MCYCLEH) := cycle64(63,32)
  // mvendorid & marchid
  csr(CSR_MVENDOR) := 0x79737978.U  // ysyx
  csr(CSR_MARCH  ) := 0x018CE26E.U  // moongrt - 26010030
  // Read
  io.rdata := MuxCase(csr(csrid), Seq(
    (io.csrSel === CSR.E   ) -> csr(CSR_MTVEC),  // mtvec
    (io.csrSel === CSR.MRET) -> csr(CSR_MEPC ),  // mepc
  ))
  // Write
  val csrWen = io.csrSel.isOneOf(CSR.W, CSR.S, CSR.C)
  when (csrWen) {
    csr(csrid) := MuxCase(io.wdata, Seq(
      (io.csrSel === CSR.W) -> io.wdata,
      (io.csrSel === CSR.S) -> (csr(csrid) |  io.wdata),
      (io.csrSel === CSR.C) -> (csr(csrid) & ~io.wdata),
    ))
  }
  // ECALL
  when (io.csrSel === CSR.E) {
    csr(CSR_MSTATUS) := 0x00001800.U
    csr(CSR_MEPC   ) := io.pc
    csr(CSR_MCAUSE ) := 11.U
  }
  // MRET
  when (io.csrSel === CSR.MRET) {
    csr(CSR_MSTATUS) := 0x00000080.U
  }
  // -------- DiffTest --------
  val diffcsr = Module(new DiffCSR)
  for (i <- 0 until CSRNum) {
    diffcsr.io.csr(i) := csr(i)
  }
}

// ----------------------------------
// IDU: Instruction Decode Unit
// ----------------------------------
class IDUOut extends Bundle{
  val exSel   = EX()
  val lsSel   = LS()
  val gprSel  = GPR()
  val gprAddr = UInt(log2Ceil(GPRNum).W)
  val pc      = UInt(DataWidth.W)
  val csrData = UInt(DataWidth.W)
  val RS2     = UInt(DataWidth.W)
  val op1     = UInt(DataWidth.W)
  val op2     = UInt(DataWidth.W)
  val immsb   = UInt(DataWidth.W)
}
class IDU extends Module {
  val io = IO(new Bundle {
    val ifuin = Flipped(Decoupled(new IFUOut))
    val wbuin = Flipped(Decoupled(new WBUOut))
    val out = Decoupled(new IDUOut)
  })
  // -----------------------------------------------
  // -------------------- State --------------------
  // -----------------------------------------------
  // private val sIdle :: sWait :: Nil = Enum(2)
  // val state = RegInit(sIdle)
  // state := MuxLookup(state, sIdle)(List(
  //   sIdle -> Mux(io.ifuin.fire, sWait, sIdle),
  //   sWait -> Mux(io.out.fire, sIdle, sWait)
  // ))
  io.ifuin.ready := true.B
  io.wbuin.ready := true.B
  io.out.valid   := io.ifuin.fire
  // -----------------------------------------------
  // -------------------- Input --------------------
  // -----------------------------------------------
  val pc      = io.ifuin.bits.pc
  val inst    = io.ifuin.bits.inst
  val gprWen  = io.wbuin.bits.gprWen
  val gprAddr = io.wbuin.bits.gprAddr
  val gprData = io.wbuin.bits.gprData
  // -----------------------------------------------
  // -------------------- Logic --------------------
  // -----------------------------------------------
  val List(op1Sel, op2Sel, csrSel, exSel, lsSel, gprSel) = ListLookup(inst,
    List(OP1.RS1, OP2.RS2, CSR.NONE, EX.ADD, LS.NONE, GPR.EX), Array(
      // Load/Store
      LW     -> List(OP1.RS1 , OP2.IMI , CSR.NONE, EX.ADD , LS.RW  , GPR.LS  ),  // x[rs1] + sext(immi)
      LH     -> List(OP1.RS1 , OP2.IMI , CSR.NONE, EX.ADD , LS.RH  , GPR.LS  ),  // x[rs1] + sext(immi)
      LB     -> List(OP1.RS1 , OP2.IMI , CSR.NONE, EX.ADD , LS.RB  , GPR.LS  ),  // x[rs1] + sext(immi)
      LHU    -> List(OP1.RS1 , OP2.IMI , CSR.NONE, EX.ADD , LS.RHU , GPR.LS  ),  // x[rs1] + sext(immi)
      LBU    -> List(OP1.RS1 , OP2.IMI , CSR.NONE, EX.ADD , LS.RBU , GPR.LS  ),  // x[rs1] + sext(immi)
      SW     -> List(OP1.RS1 , OP2.IMS , CSR.NONE, EX.ADD , LS.WW  , GPR.NONE),  // x[rs1] + sext(imms)
      SH     -> List(OP1.RS1 , OP2.IMS , CSR.NONE, EX.ADD , LS.WH  , GPR.NONE),  // x[rs1] + sext(imms)
      SB     -> List(OP1.RS1 , OP2.IMS , CSR.NONE, EX.ADD , LS.WB  , GPR.NONE),  // x[rs1] + sext(imms)
      LUI    -> List(OP1.NONE, OP2.IMU , CSR.NONE, EX.ADD , LS.NONE, GPR.EX  ),  // sext(immu[31:12] << 12)
      AUIPC  -> List(OP1.PC  , OP2.IMU , CSR.NONE, EX.ADD , LS.NONE, GPR.EX  ),  // PC + sext(immu[31:12] << 12)
      // Arithmetic
      ADD    -> List(OP1.RS1 , OP2.RS2 , CSR.NONE, EX.ADD , LS.NONE, GPR.EX  ),  // x[rs1] + x[rs2]
      ADDI   -> List(OP1.RS1 , OP2.IMI , CSR.NONE, EX.ADD , LS.NONE, GPR.EX  ),  // x[rs1] + sext(immi)
      SUB    -> List(OP1.RS1 , OP2.RS2 , CSR.NONE, EX.SUB , LS.NONE, GPR.EX  ),  // x[rs1] - x[rs2]
      AND    -> List(OP1.RS1 , OP2.RS2 , CSR.NONE, EX.AND , LS.NONE, GPR.EX  ),  // x[rs1] & x[rs2]
      OR     -> List(OP1.RS1 , OP2.RS2 , CSR.NONE, EX.OR  , LS.NONE, GPR.EX  ),  // x[rs1] | x[rs2]
      XOR    -> List(OP1.RS1 , OP2.RS2 , CSR.NONE, EX.XOR , LS.NONE, GPR.EX  ),  // x[rs1] ^ x[rs2]
      ANDI   -> List(OP1.RS1 , OP2.IMI , CSR.NONE, EX.AND , LS.NONE, GPR.EX  ),  // x[rs1] & sext(immi)
      ORI    -> List(OP1.RS1 , OP2.IMI , CSR.NONE, EX.OR  , LS.NONE, GPR.EX  ),  // x[rs1] | sext(immi)
      XORI   -> List(OP1.RS1 , OP2.IMI , CSR.NONE, EX.XOR , LS.NONE, GPR.EX  ),  // x[rs1] ^ sext(immi)
      SLL    -> List(OP1.RS1 , OP2.RS2 , CSR.NONE, EX.SLL , LS.NONE, GPR.EX  ),  // x[rs1] << x[rs2](4,0)
      SRL    -> List(OP1.RS1 , OP2.RS2 , CSR.NONE, EX.SRL , LS.NONE, GPR.EX  ),  // x[rs1] >>u x[rs2](4,0)
      SRA    -> List(OP1.RS1 , OP2.RS2 , CSR.NONE, EX.SRA , LS.NONE, GPR.EX  ),  // x[rs1] >>s x[rs2](4,0)
      SLLI   -> List(OP1.RS1 , OP2.IMI , CSR.NONE, EX.SLL , LS.NONE, GPR.EX  ),  // x[rs1] << immsi(4,0)
      SRLI   -> List(OP1.RS1 , OP2.IMI , CSR.NONE, EX.SRL , LS.NONE, GPR.EX  ),  // x[rs1] >>u immsi(4,0)
      SRAI   -> List(OP1.RS1 , OP2.IMI , CSR.NONE, EX.SRA , LS.NONE, GPR.EX  ),  // x[rs1] >>s immsi(4,0)
      SLT    -> List(OP1.RS1 , OP2.RS2 , CSR.NONE, EX.SLT , LS.NONE, GPR.EX  ),  // x[rs1] <s x[rs2]
      SLTU   -> List(OP1.RS1 , OP2.RS2 , CSR.NONE, EX.SLTU, LS.NONE, GPR.EX  ),  // x[rs1] <u x[rs2]
      SLTI   -> List(OP1.RS1 , OP2.IMI , CSR.NONE, EX.SLT , LS.NONE, GPR.EX  ),  // x[rs1] <s immsi
      SLTIU  -> List(OP1.RS1 , OP2.IMI , CSR.NONE, EX.SLTU, LS.NONE, GPR.EX  ),  // x[rs1] <u immsi
      // Branch
      BEQ    -> List(OP1.RS1 , OP2.RS2 , CSR.NONE, EX.BEQ , LS.NONE, GPR.NONE),  // x[rs1] === x[rs2] then PC+sext(imm_b)
      BNE    -> List(OP1.RS1 , OP2.RS2 , CSR.NONE, EX.BNE , LS.NONE, GPR.NONE),  // x[rs1] =/= x[rs2] then PC+sext(imm_b)
      BGE    -> List(OP1.RS1 , OP2.RS2 , CSR.NONE, EX.BGE , LS.NONE, GPR.NONE),  // x[rs1] >=s x[rs2] then PC+sext(imm_b)
      BGEU   -> List(OP1.RS1 , OP2.RS2 , CSR.NONE, EX.BGEU, LS.NONE, GPR.NONE),  // x[rs1] >=u x[rs2] then PC+sext(imm_b)
      BLT    -> List(OP1.RS1 , OP2.RS2 , CSR.NONE, EX.BLT , LS.NONE, GPR.NONE),  // x[rs1] <s x[rs2]  then PC+sext(imm_b)
      BLTU   -> List(OP1.RS1 , OP2.RS2 , CSR.NONE, EX.BLTU, LS.NONE, GPR.NONE),  // x[rs1] <u x[rs2]  then PC+sext(imm_b)
      JAL    -> List(OP1.PC  , OP2.IMJ , CSR.NONE, EX.JAL , LS.NONE, GPR.PC  ),  // x[rd] <- PC+4 and PC+sext(imm_j)
      JALR   -> List(OP1.RS1 , OP2.IMI , CSR.NONE, EX.JAL , LS.NONE, GPR.PC  ),  // x[rd] <- PC+4 and (x[rs1]+sext(imm_i))&~1
      // CSR
      CSRRW  -> List(OP1.RS1 , OP2.CSR , CSR.W   , EX.ADD , LS.NONE, GPR.CSR ),  // CSRs[csr] <- x[rs1]
      CSRRWI -> List(OP1.IMZ , OP2.CSR , CSR.W   , EX.ADD , LS.NONE, GPR.CSR ),  // CSRs[csr] <- uext(imm_z)
      CSRRS  -> List(OP1.RS1 , OP2.CSR , CSR.S   , EX.ADD , LS.NONE, GPR.CSR ),  // CSRs[csr] <- CSRs[csr] | x[rs1]
      CSRRSI -> List(OP1.IMZ , OP2.CSR , CSR.S   , EX.ADD , LS.NONE, GPR.CSR ),  // CSRs[csr] <- CSRs[csr] | uext(imm_z)
      CSRRC  -> List(OP1.RS1 , OP2.CSR , CSR.C   , EX.ADD , LS.NONE, GPR.CSR ),  // CSRs[csr] <- CSRs[csr]&~x[rs1]
      CSRRCI -> List(OP1.IMZ , OP2.CSR , CSR.C   , EX.ADD , LS.NONE, GPR.CSR ),  // CSRs[csr] <- CSRs[csr]&~uext(imm_z)
      // Exception
      EBREAK -> List(OP1.NONE, OP2.NONE, CSR.B   , EX.NONE, LS.NONE, GPR.NONE),
      ECALL  -> List(OP1.NONE, OP2.CSR , CSR.E   , EX.CSR , LS.NONE, GPR.NONE),
      MRET   -> List(OP1.NONE, OP2.CSR , CSR.MRET, EX.CSR , LS.NONE, GPR.NONE),
    ),
  )

  // -------- Instruction Decoding --------
  val rd  = inst(11,7)
  val rs1 = inst(19,15)
  val rs2 = inst(24,20)
  // sext 12bit value to 32bit value.
  val immi = inst(31,20)  // imm for I-type
  val immsi = Cat(Fill(20, immi(11)), immi)
  val imms = Cat(inst(31,25), inst(11,7))  // imm for S-type
  val immss = Cat(Fill(20, imms(11)), imms)
  // Decode imm of B-type instruction
  val immb = Cat(inst(31), inst(7), inst(30,25), inst(11,8))
  val immsb = Cat(Fill(19, immb(11)), immb, 0.U(1.W))
  // Decode imm of J-type instruction
  val immj = Cat(inst(31), inst(19,12), inst(20), inst(30,21))
  val immsj = Cat(Fill(11, immj(19)), immj, 0.U(1.W))  // Set LSB to zero
  // Decode imm of U-type instruction
  val immu = Cat(inst(31,12), Fill(12, 0.U))  // for LUI and AUIPC
  // Decode imm of I-type instruction
  val immz = inst(19, 15)
  val immuz = Cat(Fill(27, 0.U), immz)  // for CSR instructions

  // -------- Registers --------
  val op1 = Wire(UInt(DataWidth.W))
  val op2 = Wire(UInt(DataWidth.W))
  val csr = Module(new CSRFile)
  csr.io.csrSel := csrSel
  csr.io.pc     := pc
  csr.io.addr   := immi
  csr.io.wdata  := op1
  val gpr = Module(new GPRFile)
  gpr.io.wen   := gprWen
  gpr.io.waddr := gprAddr
  gpr.io.wdata := gprData
  gpr.io.rs1   := rs1
  gpr.io.rs2   := rs2

  // -------- EX --------
  dontTouch(op1Sel)
  dontTouch(op2Sel)
  // Determine 1st operand data signal
  op1 := MuxCase(0.U, Seq(
    (op1Sel === OP1.RS1) -> gpr.io.RS1,
    (op1Sel === OP1.PC ) -> pc,
    (op1Sel === OP1.IMZ) -> immuz,
  ))
  // Determine 2nd operand data signal
  op2 := MuxCase(0.U, Seq(
    (op2Sel === OP2.RS2) -> gpr.io.RS2,
    (op2Sel === OP2.CSR) -> csr.io.rdata,
    (op2Sel === OP2.IMI) -> immsi,
    (op2Sel === OP2.IMS) -> immss,
    (op2Sel === OP2.IMJ) -> immsj,
    (op2Sel === OP2.IMU) -> immu,  // for LUI and AUIPC
  ))

  // -----------------------------------------------
  // -------------------- Output -------------------
  // -----------------------------------------------
  io.out.bits.exSel   := exSel
  io.out.bits.lsSel   := lsSel
  io.out.bits.gprSel  := gprSel
  io.out.bits.gprAddr := rd
  io.out.bits.op1     := op1
  io.out.bits.op2     := op2
  io.out.bits.RS2     := gpr.io.RS2
  io.out.bits.immsb   := immsb
  io.out.bits.csrData := csr.io.rdata
  // pass through
  io.out.bits.pc      := pc
  // -----------------------------------------------
  // -------------------- Trap ---------------------
  // -----------------------------------------------
  val trap = Module(new Trap(Riscv32E_IMPLED))
  trap.io.valid := !reset.asBool && io.ifuin.fire
  trap.io.inst  := inst
}
