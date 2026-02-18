package riscv

import chisel3._
import chisel3.util._

// ---------------------------
// ROM BlackBox (只读指令存储器)
// ---------------------------
class ROM_DPI extends BlackBox(Map("SIZE" -> 1024)) with HasBlackBoxInline {
  val io = IO(new Bundle {
    val addr = Input(UInt(32.W))
    val data = Output(UInt(32.W))
  })

  // Verilog 内联实现（DPI-C 或系统存储器可在这里实现）
  setInline("ROM_DPI.v",
    s"""
      |module ROM_DPI #(parameter SIZE = 1024)(
      |  input  wire [31:0] addr,
      |  output wire [31:0] data
      |);
      |  // DPI-C 接口示例（由外部 C 实现实际数据）
      |  import "DPI-C" function void rom_dpi(input logic [31:0] addr, output logic [31:0] data);
      |  logic [31:0] tmp;
      |  always_comb begin
      |    rom_dpi(addr, tmp);
      |  end
      |  assign data = tmp;
      |endmodule
    """.stripMargin)
}

// ---------------------------
// RAM BlackBox (可读写数据存储器)
// ---------------------------
class RAM_DPI extends BlackBox(Map("SIZE" -> 1024)) with HasBlackBoxInline {
  val io = IO(new Bundle {
    val addr  = Input(UInt(32.W))
    val wdata = Input(UInt(32.W))
    val rdata = Output(UInt(32.W))
    val we    = Input(Bool())
  })

  setInline("RAM_DPI.v",
    s"""
      |module RAM_DPI #(parameter SIZE = 1024)(
      |  input  wire [31:0] addr,
      |  input  wire [31:0] wdata,
      |  input  wire        we,
      |  output wire [31:0] rdata
      |);
      |  // DPI-C 接口示例（由外部 C 实现实际数据）
      |  import "DPI-C" function void ram_dpi(input logic [31:0] addr, input logic [31:0] wdata, input logic we, output logic [31:0] rdata);
      |  logic [31:0] tmp;
      |  always_comb begin
      |    ram_dpi(addr, wdata, we, tmp);
      |  end
      |  assign rdata = tmp;
      |endmodule
    """.stripMargin)
}

// ---------------------------
// Trap BlackBox (异常处理模块)
// ---------------------------
class Trap_DPI extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val trap = Input(Bool())
  })

  setInline("Trap_DPI.v",
    """
    |module Trap_DPI(input wire trap);
    |  import "DPI-C" function void nemu_trap();
    |  always @(*) begin
    |    if (trap) nemu_trap();
    |  end
    |endmodule
    """.stripMargin)
}

// ---------------------------
// IF 模块：Instruction Fetch
// ---------------------------
class IF extends Module {
  val io = IO(new Bundle {
    val pc_next = Input(UInt(32.W))   // 下一个 PC
    val instr   = Input(UInt(32.W))   // 外部提供指令
    val pc_out  = Output(UInt(32.W))  // 当前 PC 输出
  })

  val pc = RegInit("h80000000".U(32.W))
  pc := io.pc_next
  io.pc_out := pc
}

// ---------------------------
// ID 模块：Instruction Decode + GPR
// ---------------------------
class ID extends Module {
  val io = IO(new Bundle {
    val instr     = Input(UInt(32.W))
    val pc        = Input(UInt(32.W))
    val rs1_data  = Output(UInt(32.W))
    val rs2_data  = Output(UInt(32.W))
    val rd_addr   = Output(UInt(5.W))
    val imm       = Output(UInt(32.W))
    val alu_op    = Output(UInt(4.W))
    val mem_read  = Output(Bool())
    val mem_write = Output(Bool())
    val reg_write = Output(Bool())
    val jalr      = Output(Bool())
  })

  val regfile = RegInit(VecInit(Seq.fill(32)(0.U(32.W))))

  val opcode = io.instr(6,0)
  val rd     = io.instr(11,7)
  val rs1    = io.instr(19,15)
  val rs2    = io.instr(24,20)

  io.rs1_data := regfile(rs1)
  io.rs2_data := regfile(rs2)
  io.rd_addr  := rd

  val imm_i = io.instr(31,20)
  val imm_u = io.instr(31,12) << 12
  val imm_s = Cat(io.instr(31,25), io.instr(11,7))
  io.imm := MuxLookup(opcode, 0.U)(Seq(
    "b0010011".U -> imm_i.asSInt.pad(32).asUInt,
    "b0110111".U -> imm_u.asSInt.pad(32).asUInt,
    "b0000011".U -> imm_i.asSInt.pad(32).asUInt,
    "b0100011".U -> imm_s.asSInt.pad(32).asUInt,
    "b1100111".U -> imm_i.asSInt.pad(32).asUInt
  ))

  io.alu_op := MuxLookup(opcode, 0.U)(Seq(
    "b0110011".U -> 0.U,
    "b0010011".U -> 1.U,
    "b0110111".U -> 2.U,
    "b0000011".U -> 1.U,
    "b0100011".U -> 1.U,
    "b1100111".U -> 1.U
  ))

  io.mem_read  := (opcode === "b0000011".U)
  io.mem_write := (opcode === "b0100011".U)
  io.reg_write := (opcode === "b0110011".U || opcode === "b0010011".U ||
                   opcode === "b0000011".U || opcode === "b0110111".U ||
                   opcode === "b1100111".U)
  io.jalr := (opcode === "b1100111".U)

  val trap = Module(new Trap_DPI)
  trap.io.trap := (opcode === "b1110011".U)
}

// ---------------------------
// EX 模块
// ---------------------------
class EX extends Module {
  val io = IO(new Bundle {
    val rs1     = Input(UInt(32.W))
    val rs2     = Input(UInt(32.W))
    val imm     = Input(UInt(32.W))
    val alu_op  = Input(UInt(4.W))
    val alu_out = Output(UInt(32.W))
    val mem_addr= Output(UInt(32.W))
    val jalr    = Input(Bool())
    val pc      = Input(UInt(32.W))
    val pc_next = Output(UInt(32.W))
  })

  io.alu_out := MuxLookup(io.alu_op, 0.U)(Seq(
    0.U -> (io.rs1 + io.rs2),
    1.U -> (io.rs1 + io.imm),
    2.U -> io.imm
  ))

  io.mem_addr := io.rs1 + io.imm
  io.pc_next := Mux(io.jalr, (io.rs1 + io.imm) & ~1.U(32.W), io.pc + 4.U)
}

// ---------------------------
// ROM 模块（只读指令存储器）
// ---------------------------
class ROM(size: Int) extends Module {
  val io = IO(new Bundle {
    val addr  = Input(UInt(32.W))
    val data  = Output(UInt(32.W))
  })

  val mem = Mem(size, UInt(32.W))
  // TODO: 这里可以通过 loadMemoryFromFileInline("program.hex") 初始化
  io.data := mem(io.addr >> 2)
}

// ---------------------------
// RAM 模块（数据存储器）
// ---------------------------
class RAM(size: Int) extends Module {
  val io = IO(new Bundle {
    val addr  = Input(UInt(32.W))
    val wdata = Input(UInt(32.W))
    val rdata = Output(UInt(32.W))
    val we    = Input(Bool())
  })

  val mem = Mem(size, UInt(32.W))
  io.rdata := mem(io.addr >> 2)
  when(io.we) { mem(io.addr >> 2) := io.wdata }
}

// ---------------------------
// MiniRV CPU
// ---------------------------
class MiniRV extends Module {
  val io = IO(new Bundle {
    val pc        = Output(UInt(32.W))
    val instr     = Input(UInt(32.W))
    val mem_rdata = Input(UInt(32.W))
    val mem_wdata = Output(UInt(32.W))
    val mem_addr  = Output(UInt(32.W))
    val mem_we    = Output(Bool())
  })

  val ifStage = Module(new IF)
  val idStage = Module(new ID)
  val exStage = Module(new EX)

  // IF -> ID
  idStage.io.instr := ifStage.io.instr
  idStage.io.pc    := ifStage.io.pc_out
  io.pc            := ifStage.io.pc_out
  ifStage.io.instr := io.instr

  // ID -> EX
  exStage.io.rs1    := idStage.io.rs1_data
  exStage.io.rs2    := idStage.io.rs2_data
  exStage.io.imm    := idStage.io.imm
  exStage.io.alu_op := idStage.io.alu_op
  exStage.io.jalr   := idStage.io.jalr
  exStage.io.pc     := ifStage.io.pc_out

  // Memory
  io.mem_addr  := exStage.io.mem_addr
  io.mem_wdata := idStage.io.rs2_data
  io.mem_we    := idStage.io.mem_write

  // PC update
  ifStage.io.pc_next := exStage.io.pc_next
}

// ---------------------------
// MiniRV SOC：自包含 CPU + ROM + RAM
// ---------------------------
class MiniRVSOC extends Module {
  val io = IO(new Bundle {})

  val cpu = Module(new MiniRV)
  val rom = Module(new ROM_DPI)
  val ram = Module(new RAM_DPI)

  // IF: CPU 从 ROM 取指令
  rom.io.addr  := cpu.io.pc
  cpu.io.instr := rom.io.data

  // MEM: CPU 数据访问 RAM
  ram.io.addr  := cpu.io.mem_addr
  ram.io.wdata := cpu.io.mem_wdata
  ram.io.we    := cpu.io.mem_we
  cpu.io.mem_rdata := ram.io.rdata
}
