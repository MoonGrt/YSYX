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
  val OP1_IMZ  = 2.U(OP1_SEL_LEN.W)
  val OP1_NONE = 3.U(OP1_SEL_LEN.W)

  val OP2_SEL_LEN = 3
  val OP2_NONE = 0.U(OP2_SEL_LEN.W)
  val OP2_RS2  = 1.U(OP2_SEL_LEN.W)
  val OP2_IMI  = 2.U(OP2_SEL_LEN.W)
  val OP2_IMS  = 3.U(OP2_SEL_LEN.W)
  val OP2_IMJ  = 4.U(OP2_SEL_LEN.W)
  val OP2_IMU  = 5.U(OP2_SEL_LEN.W)

  val EX_SEL_LEN = 1
  val EX_ADD  = 0.U(EX_SEL_LEN.W)

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
exsel   := 0.U
op1     := 0.U
op2     := 0.U
rd_addr := 0.U
halt   := 0.U
jumpen := 0.U
memBen := 0.U
memRen := 0.U
memWen := 0.U
regWen := 0.U
regfileOut := 0.U
}

// ---------------------------
// EX 模块
// ---------------------------
class Riscv32E_EX extends Module {
  import Riscv32E_Parameters._
  val io = IO(new Bundle {
    val op1   = Input(UInt(32.W))
    val op2   = Input(UInt(32.W))
    val exsel = Input(UInt(EX_SEL_LEN.W))
    val exout = Output(UInt(32.W))
  })
  // -------- ALU --------
  io.exout := MuxCase(0.U(32.W), Seq(
    (io.exsel === EX_ADD) -> (io.op1 + io.op2),
  ))
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
  exStage.io.op1   := idStage.io.op1
  exStage.io.op2   := idStage.io.op2
  exStage.io.exsel := idStage.io.exsel

  // Memory
  io.mem_re    := idStage.io.memRen
  io.mem_we    := idStage.io.memWen
  io.mem_addr  := exStage.io.exout
  io.mem_wdata := idStage.io.op2
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
