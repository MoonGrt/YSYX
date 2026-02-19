package rv32

package riscv

import chisel3._
import chisel3.util._

// // ---------------------------
// // ROM BlackBox (只读指令存储器)
// // ---------------------------
// class ROM_DPI extends BlackBox with HasBlackBoxInline {
//   val io = IO(new Bundle {
//     val addr = Input(UInt(32.W))
//     val data = Output(UInt(32.W))
//   })
//   // Verilog 内联实现（DPI-C 或系统存储器可在这里实现）
//   setInline("ROM_DPI.v",
//     s"""
//       |import "DPI-C" function void pmem_read(input int addr, output int data);
//       |module ROM_DPI(
//       |  input  wire [31:0] addr,
//       |  output wire [31:0] data
//       |);
//       |  always @(*) data = pmem_read(addr);
//       |endmodule
//     """.stripMargin)
// }

// // ---------------------------
// // RAM BlackBox (可读写数据存储器)
// // ---------------------------
// class RAM_DPI extends BlackBox with HasBlackBoxInline {
//   val io = IO(new Bundle {
//     val we    = Input(Bool())
//     val addr  = Input(UInt(32.W))
//     val mask  = Input(UInt(8.W))
//     val wdata = Input(UInt(32.W))
//     val rdata = Output(UInt(32.W))
//   })
//   // Verilog 内联实现（DPI-C 或系统存储器可在这里实现）
//   setInline("RAM_DPI.v",
//     s"""
//       |import "DPI-C" function int  pmem_read(input int raddr);
//       |import "DPI-C" function void pmem_write(input int waddr, input int wdata, input byte wmask);
//       |module RAM_DPI(
//       |  input  wire        we,
//       |  input  wire [31:0] addr,
//       |  input  wire [ 7:0] mask,
//       |  input  wire [31:0] wdata,
//       |  output wire [31:0] rdata
//       |);
//       |  always @(*) begin
//       |    rdata = pmem_read(addr);
//       |    if (we) pmem_write(addr, wdata, wmask);
//       |  end
//       |endmodule
//     """.stripMargin)
// }

// // ---------------------------
// // EBreak BlackBox (异常处理模块)
// // ---------------------------
// class EBreak_DPI extends BlackBox with HasBlackBoxInline {
//   val io = IO(new Bundle {
//     val trap = Input(Bool())
//   })
//   // Verilog 内联实现（DPI-C 或系统存储器可在这里实现）
//   setInline("EBreak_DPI.v",
//     s"""
//       |import "DPI-C" function void ebreak();
//       |module EBreak_DPI(input wire trap);
//       |  always @(*) if (trap) ebreak();
//       |endmodule
//     """.stripMargin)
// }

// ---------------------------
// ROM BlackBox (只读指令存储器)
// ---------------------------
class ROM_DPI extends BlackBox{
  val io = IO(new Bundle {
    val addr = Input(UInt(32.W))
    val data = Output(UInt(32.W))
  })
}

// ---------------------------
// RAM BlackBox (可读写数据存储器)
// ---------------------------
class RAM_DPI extends BlackBox {
  val io = IO(new Bundle {
    val we    = Input(Bool())
    val addr  = Input(UInt(32.W))
    val mask  = Input(UInt(8.W))
    val wdata = Input(UInt(32.W))
    val rdata = Output(UInt(32.W))
  })
}

// ---------------------------
// EBreak BlackBox (异常处理模块)
// ---------------------------
class EBreak extends BlackBox {
  val io = IO(new Bundle {
    val trap = Input(Bool())
    val code = Input(UInt(8.W))
  })
}

// ---------------------------
// 工具：符号扩展
// ---------------------------
object Sext {
  def apply(x: UInt, bits: Int): UInt = {
    Cat(Fill(32 - bits, x(bits - 1)), x)
  }
}

// ---------------------------
// IF 模块：Instruction Fetch
// ---------------------------
class IF extends Module {
  val io = IO(new Bundle {
    val pc_next = Input(UInt(32.W))   // 下一个 PC
    val pc_out  = Output(UInt(32.W))  // 当前 PC 输出
  })
  val pc = RegInit("h80000000".U(32.W))
  pc := io.pc_next
  io.pc_out := pc
}

// ---------------------------
// ID 模块：Instruction Decode + GPR
// ---------------------------
object Instructions {
  // Load/Store
  val LW      = BitPat("b?????????????????010?????0000011")
  val LBU     = BitPat("b?????????????????100?????0000011")
  val SW      = BitPat("b?????????????????010?????0100011")
  val SB      = BitPat("b?????????????????000?????0100011")
  // Add
  val ADD     = BitPat("b0000000??????????000?????0110011")
  val ADDI    = BitPat("b?????????????????000?????0010011")
  // Jump
  val JALR    = BitPat("b?????????????????000?????1100111")
  // Load immediate
  val LUI     = BitPat("b?????????????????????????0110111")
  // EBreak
  val EBREAK  = BitPat("b000000000001000000000000011100111")
}
object Parameters {
  val EX_SEL_LEN = 2
  val EX_ADD  = 0.U(EX_SEL_LEN.W)
  val EX_JALR = 0.U(EX_SEL_LEN.W)

  val WB_SEL_LEN = 1
  val WB_EX  = 0.U(WB_SEL_LEN.W)
  val WB_MEM = 1.U(WB_SEL_LEN.W)

  val MEM_SEL_LEN = 2
  val MEM_WW = 0.U(MEM_SEL_LEN.W)  // write word
  val MEM_WB = 0.U(MEM_SEL_LEN.W)  // write byte
  val MEM_RW = 0.U(MEM_SEL_LEN.W)
  val MEM_RB = 0.U(MEM_SEL_LEN.W)
}
class ID extends Module {
  val io = IO(new Bundle {
    val instr     = Input(UInt(32.W))
    val pc        = Input(UInt(32.W))

    // 写回接口（来自 WB）
    val wb_en     = Input(Bool())
    val wb_rd     = Input(UInt(5.W))
    val wb_data   = Input(UInt(32.W))

    // 输出到 EX
    val rs1_data  = Output(UInt(32.W))
    val rs2_data  = Output(UInt(32.W))
    val rd_addr   = Output(UInt(5.W))
    val imm       = Output(UInt(32.W))

    val alu_op    = Output(UInt(2.W))
    val mem_read  = Output(Bool())
    val mem_write = Output(Bool())
    val reg_write = Output(Bool())
    val jalr      = Output(Bool())
  })









  // -------- 寄存器堆 --------
  val regfile = RegInit(VecInit(Seq.fill(32)(0.U(32.W))))

  // 写回（x0 永远忽略）
  when (io.wb_en && io.wb_rd =/= 0.U) {
    regfile(io.wb_rd) := io.wb_data
  }

  // -------- 指令字段 --------
  val opcode = io.instr(6,0)
  val rd     = io.instr(11,7)
  val rs1    = io.instr(19,15)
  val rs2    = io.instr(24,20)

  // -------- 读寄存器（x0 = 0）--------
  io.rs1_data := Mux(rs1 === 0.U, 0.U, regfile(rs1))
  io.rs2_data := Mux(rs2 === 0.U, 0.U, regfile(rs2))
  io.rd_addr  := rd

  // -------- 立即数（严格对齐 C 模型）--------
  val imm_i = Sext(io.instr(31,20), 12)
  val imm_s = Sext(Cat(io.instr(31,25), io.instr(11,7)), 12)
  val imm_u = io.instr(31,12) << 12

  io.imm := MuxLookup(opcode, 0.U)(Seq(
    "b0010011".U -> imm_i,  // ADDI
    "b0000011".U -> imm_i,  // LOAD
    "b0100011".U -> imm_s,  // STORE
    "b0110111".U -> imm_u,  // LUI
    "b1100111".U -> imm_i   // JALR
  ))

  // -------- 控制信号 --------
  io.alu_op := MuxLookup(opcode, 0.U)(Seq(
    "b0110011".U -> 0.U,  // ADD
    "b0010011".U -> 1.U,  // ADDI
    "b0000011".U -> 1.U,  // LOAD
    "b0100011".U -> 1.U,  // STORE
    "b0110111".U -> 1.U,  // LUI
    "b1100111".U -> 1.U   // JALR
  ))

  io.mem_read  := (opcode === "b0000011".U)
  io.mem_write := (opcode === "b0100011".U)
  io.reg_write := ~io.mem_write
  io.jalr := opcode === "b1100111".U

  val trap = Module(new EBreak)
  trap.io.trap := (io.instr === "h00100073".U)
  trap.io.code := 0.U(8.W)
}

// ---------------------------
// EX 模块
// ---------------------------
class EX extends Module {
  val io = IO(new Bundle {
    val rs1     = Input(UInt(32.W))
    val rs2     = Input(UInt(32.W))
    val imm     = Input(UInt(32.W))
    val alu_op  = Input(UInt(2.W))
    val pc      = Input(UInt(32.W))
    val jalr    = Input(Bool())

    val alu_out = Output(UInt(32.W))
    val mem_addr= Output(UInt(32.W))
    val pc_next = Output(UInt(32.W))
  })

  // -------- ALU --------
  io.alu_out := MuxLookup(io.alu_op, 0.U)(Seq(
    0.U -> (io.rs1 + io.rs2),  // ADD
    1.U -> (io.rs1 + io.imm),  // ADDI / LOAD / STORE
    2.U -> io.imm              // LUI
  ))

  // -------- 地址计算 --------
  io.mem_addr := io.rs1 + io.imm

  // -------- PC 更新 --------
  io.pc_next := Mux(
    io.jalr,
    (io.rs1 + io.imm) & ~1.U(32.W),  // 对齐 C：& ~1
    io.pc + 4.U
  )
}

// ---------------------------
// MiniRV CPU（单周期）
// ---------------------------
class MiniRV extends Module {
  val io = IO(new Bundle {
    val pc    = Output(UInt(32.W))
    val instr = Input(UInt(32.W))

    val mem_we    = Output(Bool())
    val mem_addr  = Output(UInt(32.W))
    val mem_mask  = Output(UInt(8.W))
    val mem_wdata = Output(UInt(32.W))
    val mem_rdata = Input(UInt(32.W))
  })

  val ifStage = Module(new IF)
  val idStage = Module(new ID)
  val exStage = Module(new EX)

  // IF
  io.pc := ifStage.io.pc_out

  // ID
  idStage.io.instr := io.instr
  idStage.io.pc    := ifStage.io.pc_out

  // EX
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
  io.mem_mask  := "b1111".U  // 先全字写，对齐 C 的 SW

  // Write Back
  val wb_data = Mux(idStage.io.mem_read,
                    io.mem_rdata,
                    exStage.io.alu_out)

  idStage.io.wb_en   := idStage.io.reg_write
  idStage.io.wb_rd   := idStage.io.rd_addr
  idStage.io.wb_data := wb_data

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

  // 指令取值
  rom.io.addr := cpu.io.pc
  cpu.io.instr := rom.io.data

  // 数据访存
  ram.io.we    := cpu.io.mem_we
  ram.io.addr  := cpu.io.mem_addr
  ram.io.mask  := cpu.io.mem_mask
  ram.io.wdata := cpu.io.mem_wdata
  cpu.io.mem_rdata := ram.io.rdata
}
