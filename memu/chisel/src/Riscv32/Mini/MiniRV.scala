package riscv.mini

import chisel3._
import chisel3.util._
import riscv.Instructions._
import riscv.Constants._
import riscv.Constants.MiniRV._
import riscv.util._

// ---------------------------
// IFU 模块：Instruction Fetch
// ---------------------------
class IFU extends Module {
  val io = IO(new Bundle {
    val halt   = Input(Bool())  // halt 信号
    val bren   = Input(Bool())  // 跳转使能
    val braddr = Input(UInt(DataWidth.W))  // 跳转地址
    val npc    = Output(UInt(DataWidth.W))  // 下一个 PC
    val pc     = Output(UInt(DataWidth.W))  // 当前 PC 输出
  })
  val pc = RegInit("h80000000".U(DataWidth.W))
  pc := MuxCase(io.npc, Seq(
    io.halt -> pc,
    io.bren -> io.braddr,
  ))
  io.pc  := pc
  io.npc := pc + 4.U
}

// ---------------------------
// IDU 模块：Instruction Decode + GPR
// ---------------------------
class IDU extends Module {
  val io = IO(new Bundle {
    val pc      = Input(UInt(DataWidth.W))
    val inst    = Input(UInt(DataWidth.W))

    // 写回
    val wb_en   = Input(Bool())
    val wb_rd   = Input(UInt(5.W))
    val memData = Input(UInt(DataWidth.W))
    val exData  = Input(UInt(DataWidth.W))

    // 输出到 EXU
    val exsel   = Output(EX())
    val op1     = Output(UInt(DataWidth.W))
    val op2     = Output(UInt(DataWidth.W))
    val rs2     = Output(UInt(DataWidth.W))
    val rd_addr = Output(UInt(5.W))

    // Control signals
    val halt   = Output(Bool())
    val memsel = Output(MEM())
    val regWen = Output(Bool())

    // Diff
    val gprOut = Output(Vec(GPR_NUM, UInt(DataWidth.W)))
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
  val GPR = RegInit(VecInit(Seq.fill(GPR_NUM)(0.U(DataWidth.W))))

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
  // Decode imm of U-type instruction
  val immu = Cat(io.inst(31,12), Fill(12, 0.U))  // for LUI

  // -------- EX功能 --------
  io.exsel := exsel
  io.rs2 := GPR(rs2)
  // Determine 1st operand data signal
  io.op1 := Mux(io.inst === LUI, 0.U, GPR(rs1))
  // Determine 2nd operand data signal
  io.op2 := MuxCase(0.U(32.W), Seq(
    (op2sel === OP2.RS2) -> GPR(rs2),
    (op2sel === OP2.IMI) -> immsi,
    (op2sel === OP2.IMS) -> immss,
    (op2sel === OP2.IMU) -> immu,  // for LUI
  ))

  // -------- WB功能 --------
  io.memsel := memsel
  // GPR
  io.rd_addr := rd
  io.regWen  := wbsel =/= WB.NONE
  val memData = MuxLookup(io.memsel, 0.U(DataWidth.W))(Seq(
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

  // -------- Trap --------
  val trap = Module(new Trap(MiniRV_IMPLED))
  trap.io.inst := io.inst
  io.halt := trap.io.halt
}

// ---------------------------
// EXU 模块
// ---------------------------
class EXU extends Module {
  val io = IO(new Bundle {
    val pc     = Input(UInt(DataWidth.W))
    val op1    = Input(UInt(DataWidth.W))
    val op2    = Input(UInt(DataWidth.W))
    val exsel  = Input(EX())
    val aluout = Output(UInt(DataWidth.W))
    val bren   = Output(Bool())
    val braddr = Output(UInt(DataWidth.W))
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
    val pc   = Output(UInt(DataWidth.W))
    val inst = Input(UInt(DataWidth.W))

    val mem_re    = Output(Bool())
    val mem_we    = Output(Bool())
    val mem_len   = Output(UInt((DataWidth/8).W))
    val mem_addr  = Output(UInt(DataWidth.W))
    val mem_wdata = Output(UInt(DataWidth.W))
    val mem_rdata = Input(UInt(DataWidth.W))
  })

  val ifu = Module(new IFU)
  val idu = Module(new IDU)
  val exu = Module(new EXU)

  // IFU
  io.pc := ifu.io.pc
  ifu.io.bren   := exu.io.bren
  ifu.io.braddr := exu.io.braddr
  ifu.io.halt   := idu.io.halt

  // IDU
  idu.io.pc   := ifu.io.pc
  idu.io.inst := io.inst

  // EXU
  exu.io.pc    := idu.io.pc
  exu.io.op1   := idu.io.op1
  exu.io.op2   := idu.io.op2
  exu.io.exsel := idu.io.exsel

  // Memory
  val memType   = idu.io.memsel
  io.mem_re    := !reset.asBool && memType.isOneOf(MEM.RW, MEM.RBU)
  io.mem_we    := !reset.asBool && memType.isOneOf(MEM.WW, MEM.WB)
  io.mem_addr  := exu.io.aluout
  io.mem_wdata := idu.io.rs2
  io.mem_len   := Mux(memType.isOneOf(MEM.WB, MEM.RBU), 1.U, 4.U)

  // Write Back
  idu.io.wb_en   := idu.io.regWen
  idu.io.wb_rd   := idu.io.rd_addr
  idu.io.memData := io.mem_rdata
  idu.io.exData  := exu.io.aluout

  // -------- DiffTest --------
  val diffpc = Module(new DiffPC)
  diffpc.io.pc   := ifu.io.pc
  diffpc.io.npc  := Mux(exu.io.bren, exu.io.braddr, ifu.io.npc)
  diffpc.io.inst := idu.io.inst
  val diffgpr = Module(new DiffGPR)
  for (i <- 0 until GPR_NUM) {
    diffgpr.io.gpr(i) := idu.io.gprOut(i)
  }
  val diffcsr = Module(new DiffCSR)
  for (i <- 0 until CSR_NUM) {
    diffcsr.io.csr(i) := 0.U(DataWidth.W)  // 未实现 CSR
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
