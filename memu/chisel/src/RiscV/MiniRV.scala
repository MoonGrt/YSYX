package riscv

import chisel3._
import chisel3.util._
import Instructions._
import Constants._
import Constants.MiniRV._

// ---------------------------
// IF 模块：Instruction Fetch
// ---------------------------
class MiniRV_IF extends Module {
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
class MiniRV_ID extends Module {
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
    val gprOut = Output(Vec(GPR_NUM, UInt(WORD_LEN.W)))
  })

  val List(op2sel, exsel, wbsel, memsel) = ListLookup(io.inst,
    List(OP2.RS2, EX.ADD, WB.EX, MEM.NONE), Array(
      LW     -> List(OP2.IMI , EX.ADD , WB.MEM , MEM.RW  ),  // x[rs1] + sext(immi)
      LBU    -> List(OP2.IMI , EX.ADD , WB.MEM , MEM.RBU ),  // x[rs1] + sext(immi)
      SW     -> List(OP2.IMS , EX.ADD , WB.NONE, MEM.WW  ),  // x[rs1] + sext(imms)
      SB     -> List(OP2.IMS , EX.ADD , WB.NONE, MEM.WB  ),  // x[rs1] + sext(imms)
      ADD    -> List(OP2.RS2 , EX.ADD , WB.EX  , MEM.NONE),  // x[rs1] + x[rs2]
      ADDI   -> List(OP2.IMI , EX.ADD , WB.EX  , MEM.NONE),  // x[rs1] + sext(immi)
      JALR   -> List(OP2.IMI , EX.JAL , WB.PC  , MEM.NONE),  // x[rd] <- PC+4 and (x[rs1]+sext(imm_i))&~1
      LUI    -> List(OP2.IMU , EX.ADD , WB.EX  , MEM.NONE),  // sext(immu[31:12] << 12)
      EBREAK -> List(OP2.NONE, EX.NONE, WB.NONE, MEM.NONE),
    ),
  )

  // -------- 寄存器堆 --------
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
  io.op1 := GPR(rs1)
  // Determine 2nd operand data signal
  io.op2 := MuxCase(0.U(32.W), Seq(
    (op2sel === OP2.RS2) -> GPR(rs2),
    (op2sel === OP2.IMI) -> immsi,
    (op2sel === OP2.IMS) -> immss,
    (op2sel === OP2.IMU) -> immu,  // for LUI and AUIPC
  ))

  // -------- WB功能 --------
  io.memsel := memsel
  // GPR
  io.rd_addr := rd
  io.regWen  := wbsel =/= WB.NONE
  val memData = MuxLookup(io.memsel, 0.U(WORD_LEN.W))(Seq(
    MEM.RW  -> io.memData,  // LW 直接写回
    MEM.RBU -> Cat(0.U(24.W), io.memData(7,0)),  // LBU 零扩展
  ))
  when (io.wb_en && io.wb_rd =/= 0.U) {
    GPR(io.wb_rd) := MuxCase(0.U, Seq(
      (wbsel === WB.PC ) -> (io.pc + 4.U),
      (wbsel === WB.EX ) -> io.exData,
      (wbsel === WB.MEM) -> memData,
    ))
  }

  // 输出 GPR
  io.gprOut := GPR

  // -------- 异常处理 --------
  val trap = Module(new EBreak)
  // 定义异常编码规则
  // 0: EBREAK, 1: 全零指令, 2: 其他E指令, 3: 未实现指令
  val impl_inst = MiniRV_IMPLED.filterNot(inst =>
    inst == E || inst == EBREAK
  )
  val is_unimpl = ~impl_inst.map(inst => io.inst === inst).reduce(_ || _)
  val is_zero = (io.inst === 0.U)
  val is_ebreak = (io.inst === EBREAK)
  val is_otherE = (io.inst === E) && (io.inst =/= EBREAK)
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
class MiniRV_EX extends Module {
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
  io.aluout := MuxCase(0.U, Seq(
    (io.exsel === EX.ADD ) -> (io.op1 + io.op2),
  ))
  // -------- Branch --------
  io.bren := MuxCase(false.B, Seq(
    (io.exsel === EX.JAL ) -> true.B,
  ))
  io.braddr := MuxCase(0.U, Seq(
    (io.exsel === EX.JAL) -> (io.op1 + io.op2),
  ))
}

// ---------------------------
// MiniRV CPU（单周期）
// ---------------------------
class MiniRV extends Module {
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

  val ifStage = Module(new MiniRV_IF)
  val idStage = Module(new MiniRV_ID)
  val exStage = Module(new MiniRV_EX)

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
  val memType = idStage.io.memsel
  io.mem_re    := !reset.asBool && memType.isOneOf(MEM.RW, MEM.RBU)
  io.mem_we    := !reset.asBool && memType.isOneOf(MEM.WW, MEM.WB)
  io.mem_addr  := exStage.io.aluout
  io.mem_wdata := idStage.io.rs2
  io.mem_len   := Mux(memType.isOneOf(MEM.WB, MEM.RBU), 1.U, 4.U)

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
    difftest.io.csr(i) := 0.U(WORD_LEN.W)  // 未实现 CSR
  }
  for (i <- 0 until GPR_NUM) {
    difftest.io.gpr(i) := idStage.io.gprOut(i)
  }
}

// ---------------------------
// MiniRV TOP：自包含 CPU + ROM + RAM
// ---------------------------
class MiniRVTOP extends Module {
  val cpu = Module(new MiniRV)
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
