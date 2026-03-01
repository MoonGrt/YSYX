package riscv

import chisel3._
import chisel3.util._

// ---------------------------
// IF 模块：Instruction Fetch
// ---------------------------
class Riscv32E_IF extends Module {
  val io = IO(new Bundle {
    val halt   = Input(Bool())  // halt 信号
    val jumpen = Input(Bool())  // 跳转使能
    val jump   = Input(UInt(32.W))  // 跳转地址
    val npc    = Output(UInt(32.W))  // 下一个 PC
    val pc     = Output(UInt(32.W))  // 当前 PC 输出
  })
  val pc = RegInit("h80000000".U(32.W))
  when (io.halt) {
    pc := pc
  }.otherwise {
    when (io.jumpen) {
      pc := io.jump
    }.otherwise {
      pc := io.npc
    }
  }
  io.pc  := pc
  io.npc := pc + 4.U(32.W)
}

// ---------------------------
// ID 模块：Instruction Decode + GPR
// ---------------------------
object Riscv32E_Instructions {
  // Load/Store
  val LW     = BitPat("b?????????????????010?????0000011")
  val LBU    = BitPat("b?????????????????100?????0000011")
  val SW     = BitPat("b?????????????????010?????0100011")
  val SB     = BitPat("b?????????????????000?????0100011")
  // Add
  val ADD    = BitPat("b0000000??????????000?????0110011")
  val ADDI   = BitPat("b?????????????????000?????0010011")
  // Jump
  val JALR   = BitPat("b?????????????????000?????1100111")
  // Load immediate
  val LUI    = BitPat("b?????????????????????????0110111")
  val AUIPC  = BitPat("b?????????????????????????0010111")
  // E - Type
  val E      = BitPat("b?????????????????????????1110011")
  val EBREAK = BitPat("b00000000000100000000000001110011")
  // Implemented instructions
  val IMPLED = Seq(LW, LBU, SW, SB, ADD, ADDI, JALR, LUI, AUIPC, E, EBREAK)
}
object Riscv32E_Parameters {
  val OP1_SEL_LEN = 2
  val OP1_RS1  = 0.U(OP1_SEL_LEN.W)
  val OP1_PC   = 1.U(OP1_SEL_LEN.W)
  val OP1_IMZ  = 3.U(OP1_LEN.W)
  val OP1_NONE = 2.U(OP1_SEL_LEN.W)
  val OP2_SEL_LEN = 1
  val OP2_NONE = 0.U(OP2_SEL_LEN.W)
  val OP2_RS2  = 1.U(OP2_SEL_LEN.W)
  val OP2_IMI  = 2.U(OP2_SEL_LEN.W)
  val OP2_IMS  = 3.U(OP2_SEL_LEN.W)
  val OP2_IMJ  = 4.U(OP2_SEL_LEN.W)
  val OP2_IMU  = 5.U(OP2_SEL_LEN.W)

  val EX_SEL_LEN = 1
  val EX_ADD  = 0.U(EX_SEL_LEN.W)
  val EX_JALR = 1.U(EX_SEL_LEN.W)

  val JUMP_SEL_LEN = 1
  val JUMP_NONE = 0.U(JUMP_SEL_LEN.W)
  val JUMP_JALR = 1.U(JUMP_SEL_LEN.W)

  val WB_SEL_LEN = 2
  val WB_NONE = 0.U(WB_SEL_LEN.W)
  val WB_PC   = 1.U(WB_SEL_LEN.W)
  val WB_EX   = 2.U(WB_SEL_LEN.W)
  val WB_MEM  = 3.U(WB_SEL_LEN.W)

  val MEM_SEL_LEN = 3
  val MEM_NONE = 0.U(MEM_SEL_LEN.W)
  val MEM_RW   = 1.U(MEM_SEL_LEN.W)  // write word
  val MEM_RB   = 2.U(MEM_SEL_LEN.W)  // write byte
  val MEM_WW   = 3.U(MEM_SEL_LEN.W)
  val MEM_WB   = 4.U(MEM_SEL_LEN.W)
}
class Riscv32E_ID extends Module {
  import Riscv32E_Instructions._
  import Riscv32E_Parameters._
  val io = IO(new Bundle {
    val pc      = Input(UInt(32.W))
    val inst    = Input(UInt(32.W))

    // 写回接口（来自 WB）
    val wb_en   = Input(Bool())
    val wb_rd   = Input(UInt(5.W))
    val wb_data = Input(UInt(32.W))

    // 输出到 EX
    val exsel   = Output(UInt(EX_SEL_LEN.W))
    val op1     = Output(UInt(32.W))
    val op2     = Output(UInt(32.W))
    val rd_addr = Output(UInt(5.W))

    // Control signals
    val halt   = Output(Bool())
    val jumpen = Output(Bool())
    val memBen = Output(Bool())
    val memRen = Output(Bool())
    val memWen = Output(Bool())
    val regWen = Output(Bool())

    val regfileOut = Output(Vec(32, UInt(32.W)))
  })

  val List(op1sel, op2sel, exsel, jumpsel, wbsel, memsel) = ListLookup(
    io.inst,
    List(OP1_RS1, OP2_RS2, EX_ADD, JUMP_NONE, WB_EX, MEM_NONE),
    Array(
      LW    -> List( OP1_RS1, OP2_IMI, EX_ADD, JUMP_NONE, WB_MEM,  MEM_RW),  // x[rs1] + sext(imm_i)
      LBU   -> List( OP1_RS1, OP2_IMI, EX_ADD, JUMP_NONE, WB_MEM,  MEM_RB),  // x[rs1] + sext(imm_i)
      SW    -> List( OP1_RS1, OP2_IMS, EX_ADD, JUMP_NONE, WB_NONE, MEM_WW),  // x[rs1] + sext(imm_s)
      SB    -> List( OP1_RS1, OP2_IMS, EX_ADD, JUMP_NONE, WB_NONE, MEM_WB),  // x[rs1] + sext(imm_s)
      ADD   -> List( OP1_RS1, OP2_RS2, EX_ADD, JUMP_NONE, WB_EX, MEM_NONE),  // x[rs1] + x[rs2]
      ADDI  -> List( OP1_RS1, OP2_IMI, EX_ADD, JUMP_NONE, WB_EX, MEM_NONE),  // x[rs1] + sext(imm_i)
      JALR  -> List( OP1_RS1, OP2_IMI, EX_ADD, JUMP_JALR, WB_PC, MEM_NONE),  // x[rd] <- PC+4 and (x[rs1]+sext(imm_i))&~1
      LUI   -> List(OP1_NONE, OP2_IMU, EX_ADD, JUMP_NONE, WB_EX, MEM_NONE),  // sext(imm_u[31:12] << 12)
      AUIPC -> List( OP1_RS1, OP2_RS2, EX_ADD, JUMP_NONE, WB_EX, MEM_NONE),  // PC + sext(imm_u[31:12] << 12)
    ),
  )

  // -------- 寄存器堆 --------
  val regfile = RegInit(VecInit(Seq.fill(32)(0.U(32.W))))

  // -------- 指令字段 --------
  val opcode = io.inst(6,0)
  val rd     = io.inst(11,7)
  val rs1    = io.inst(19,15)
  val rs2    = io.inst(24,20)

  // -------- 立即数 --------
  // sext 12bit value to 32bit value.
  val imm_i = io.inst(31, 20) // imm for I-type
  val imm_i_sext = Cat(Fill(20, imm_i(11)), imm_i)
  val imm_s = Cat(io.inst(31, 25), io.inst(11, 7)) // imm for S-type
  val imm_s_sext = Cat(Fill(20, imm_s(11)), imm_s)
  // Decode imm of B-type instruction
  val imm_b = Cat(io.inst(31), io.inst(7), io.inst(30, 25), io.inst(11, 8))
  // imm[0] does not exist in B-type instruction. This is because the first bit of program counter
  // is always zero (p.126). Size of instruction is 32bit or 16bit, so instruction pointer (pc)
  // address always points an even address.
  val imm_b_sext = Cat(Fill(19, imm_b(11)), imm_b, 0.U(1.U))
  // Decode imm of J-type instruction
  val imm_j = Cat(io.inst(31), io.inst(19, 12), io.inst(20), io.inst(30, 21))
  val imm_j_sext = Cat(Fill(11, imm_j(19)), imm_j, 0.U(1.U)) // Set LSB to zero
  // Decode imm of U-type instruction
  val imm_u = io.inst(31, 12)
  val imm_u_shifted = Cat(imm_u, Fill(12, 0.U)) // for LUI and AUIPC
  // Decode imm of I-type instruction
  val imm_z = io.inst(19, 15)
  val imm_z_uext = Cat(Fill(27, 0.U), imm_z) // for CSR instructions

  // -------- EX操作数 --------
  // Determine 1st operand data signal
  val op1_data = MuxCase(0.U(32.W), Seq(
    (op1sel === OP1_RS1) -> regfile(rs1),
    (op1sel === OP1_PC)  -> io.pc,
    (op1sel === OP1_IMZ) -> imm_z_uext,
  ))
  // Determine 2nd operand data signal
  val op2_data = MuxCase(0.U(32.W), Seq(
    (op2sel === OP2_RS2) -> regfile(rs2),
    (op2sel === OP2_IMI) -> imm_i_sext,
    (op2sel === OP2_IMS) -> imm_s_sext,
    (op2sel === OP2_IMJ) -> imm_j_sext,
    (op2sel === OP2_IMU) -> imm_u_shifted, // for LUI and AUIPC
  ))

  // -------- JUMP功能 --------
  io.jumpen := (jumpsel === JUMP_JALR)

  // -------- EX功能 --------
  io.exsel := exsel

  // -------- WB功能 --------
  io.rd_addr := rd
  io.memBen  := ~reset.asBool && (memsel === MEM_RB) || (memsel === MEM_WB)
  io.memRen  := ~reset.asBool && (memsel === MEM_RW) || (memsel === MEM_RB)
  io.memWen  := ~reset.asBool && (memsel === MEM_WW) || (memsel === MEM_WB)
  io.regWen  := ~reset.asBool && (wbsel =/= WB_NONE)
  when (io.wb_en && io.wb_rd =/= 0.U) {
    regfile(io.wb_rd) := io.wb_data
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
  // 输出 regfile
  io.regfileOut := regfile
}

// ---------------------------
// EX 模块
// ---------------------------
class Riscv32E_EX extends Module {
  val io = IO(new Bundle {
    val rs1   = Input(UInt(32.W))
    val rs2   = Input(UInt(32.W))
    val pc    = Input(UInt(32.W))
    val imm   = Input(UInt(32.W))
    val immen = Input(Bool())
    val exsel = Input(UInt(EX_SEL_LEN.W))
    val exout = Output(UInt(32.W))
  })
  // -------- ALU --------
  io.exout := Mux(
    io.immen,
    io.rs1 + io.imm, io.rs1 + io.rs2
  )
}

// ---------------------------
// Riscv32E CPU（单周期）
// ---------------------------
class Riscv32E extends Module {
  import Riscv32E_Instructions._
  import Riscv32E_Parameters._
  val io = IO(new Bundle {
    val pc   = Output(UInt(32.W))
    val inst = Input(UInt(32.W))

    val mem_re    = Output(Bool())
    val mem_we    = Output(Bool())
    val mem_len   = Output(UInt(4.W))
    val mem_addr  = Output(UInt(32.W))
    val mem_wdata = Output(UInt(32.W))
    val mem_rdata = Input(UInt(32.W))
  })

  val ifStage = Module(new Riscv32E_IF)
  val idStage = Module(new Riscv32E_ID)
  val exStage = Module(new Riscv32E_EX)

  // IF
  io.pc := ifStage.io.pc
  ifStage.io.jumpen := idStage.io.jumpen
  ifStage.io.jump   := exStage.io.exout
  ifStage.io.halt   := idStage.io.halt

  // ID
  idStage.io.inst := io.inst

  // EX
  exStage.io.pc    := ifStage.io.pc
  exStage.io.rs1   := idStage.io.rs1
  exStage.io.rs2   := idStage.io.rs2
  exStage.io.imm   := idStage.io.imm
  exStage.io.immen := idStage.io.immen
  exStage.io.exsel := idStage.io.exsel

  // Memory
  io.mem_re    := idStage.io.memRen
  io.mem_we    := idStage.io.memWen
  io.mem_addr  := exStage.io.exout
  io.mem_wdata := idStage.io.rs2
  io.mem_len   := Mux(idStage.io.memBen, 1.U, 4.U)

  // Write Back
  val byte_shift = (exStage.io.exout(1,0) << 3)  // 位移量
  val byte_data = (io.mem_rdata >> byte_shift)(7,0)  // 取目标字节
  val mem_data = io.mem_rdata
  val wb_data = MuxCase(
    exStage.io.exout,  // 默认EX输出
    Seq(
      idStage.io.memRen -> mem_data,  // Memory read
      idStage.io.jumpen -> ifStage.io.npc  // Jump
    )
  )

  idStage.io.wb_en   := idStage.io.regWen
  idStage.io.wb_rd   := idStage.io.rd_addr
  idStage.io.wb_data := wb_data

  // DiffTest
  val difftest = Module(new DiffTest)
  difftest.io.clk  := clock
  difftest.io.pc   := ifStage.io.pc
  difftest.io.npc  := Mux(idStage.io.jumpen, exStage.io.exout, ifStage.io.npc)
  difftest.io.inst := idStage.io.inst
  for (i <- 0 until 32) {
    difftest.io.gpr(i) := idStage.io.regfileOut(i)
  }
  for (i <- 0 until 4) {
    difftest.io.csr(i) := 0.U(32.W)  // 未实现 CSR
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
