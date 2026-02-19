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
    val pcn = Input(UInt(32.W))   // 下一个 PC
    val pc  = Output(UInt(32.W))  // 当前 PC 输出
  })
  val pc = RegInit("h80000000".U(32.W))
  pc := io.pcn
  io.pc := pc
}

// ---------------------------
// ID 模块：Instruction Decode + GPR
// ---------------------------
object Instructions {
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
  // E - Type
  val E      = BitPat("b?????????????????????????1110011")
  val EBREAK = BitPat("b00000000000100000000000001110011")
  // Implemented instructions
  val IMPLEMENTED = Seq(LW, LBU, SW, SB, ADD, ADDI, JALR, LUI, E, EBREAK)
}
object Parameters {
  val EX_SEL_LEN = 1
  val EX_ADD  = 0.U(EX_SEL_LEN.W)
  val EX_JALR = 1.U(EX_SEL_LEN.W)

  val IMM_SEL_LEN = 2
  val IMMN = 0.U(IMM_SEL_LEN.W)
  val IMMI = 1.U(IMM_SEL_LEN.W)
  val IMMS = 2.U(IMM_SEL_LEN.W)
  val IMMU = 3.U(IMM_SEL_LEN.W)

  val WB_SEL_LEN = 2
  val WB_NONE = 0.U(WB_SEL_LEN.W)
  val WB_EX   = 1.U(WB_SEL_LEN.W)
  val WB_MEM  = 2.U(WB_SEL_LEN.W)

  val MEM_SEL_LEN = 3
  val MEM_NONE = 0.U(MEM_SEL_LEN.W)
  val MEM_RW   = 1.U(MEM_SEL_LEN.W)  // write word
  val MEM_RB   = 2.U(MEM_SEL_LEN.W)  // write byte
  val MEM_WW   = 3.U(MEM_SEL_LEN.W)
  val MEM_WB   = 4.U(MEM_SEL_LEN.W)
}
class ID extends Module {
  import Instructions._
  import Parameters._
  val io = IO(new Bundle {
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

    val halt   = Output(Bool())
    val memBen = Output(Bool())
    val memRen = Output(Bool())
    val memWen = Output(Bool())
    val reg_write = Output(Bool())
  })

  val decoded = ListLookup(
    io.inst,
    List(EX_ADD, IMMN, WB_EX, MEM_WW),
    Array(
      // Load/Store
      LW   -> List(EX_ADD, IMMI, WB_MEM, MEM_RW),  // x[rs1] + sext(imm_i)
      LBU  -> List(EX_ADD, IMMI, WB_MEM, MEM_RB),  // x[rs1] + sext(imm_i)
      SW   -> List(EX_ADD, IMMS, WB_NONE, MEM_WW),  // x[rs1] + sext(imm_s)
      SB   -> List(EX_ADD, IMMS, WB_NONE, MEM_WB),  // x[rs1] + sext(imm_s)
      // Add
      ADD  -> List(EX_ADD, IMMN, WB_EX, MEM_NONE),  // x[rs1] + x[rs2]
      ADDI -> List(EX_ADD, IMMI, WB_EX, MEM_NONE),  // x[rs1] + sext(imm_i)
      // Jump
      JALR -> List(EX_JALR,IMMI, WB_EX, MEM_NONE),  // x[rd] <- PC+4 and (x[rs1]+sext(imm_i))&~1
      // Load immediate
      LUI  -> List(EX_ADD, IMMU, WB_EX, MEM_NONE),  // sext(imm_u[31:12] << 12)
    ),
  )
  val exsel  = decoded(0)
  val immsel = decoded(1)
  val wbsel  = decoded(2)
  val memsel = decoded(3)

  // -------- 寄存器堆 --------
  val regfile = RegInit(VecInit(Seq.fill(32)(0.U(32.W))))

  // -------- 指令字段 --------
  val opcode = io.inst(6,0)
  val rd     = io.inst(11,7)
  val rs1    = io.inst(19,15)
  val rs2    = io.inst(24,20)

  // -------- 立即数 --------
  val imm_i = Sext(io.inst(31,20), 12)
  val imm_s = Sext(Cat(io.inst(31,25), io.inst(11,7)), 12)
  val imm_u = io.inst(31,12) << 12
  val imm = MuxLookup(immsel, 0.U)(Seq(
    IMMI -> imm_i,
    IMMS -> imm_s,
    IMMU -> imm_u
  ))

  // -------- EX操作数 --------
  val rs1_data = regfile(rs1)
  val rs2_data = regfile(rs2)
  io.op1 := rs1_data
  io.op2 := Mux(immsel === IMMN, rs2_data, imm)

  // -------- EX功能 --------
  io.exsel := exsel

  // -------- WB功能 --------
  io.rd_addr := rd
  io.memBen  := (memsel === MEM_RB) || (memsel === MEM_WB)
  io.memRen := (memsel === MEM_RW) || (memsel === MEM_RB)
  io.memWen := (memsel === MEM_WW) || (memsel === MEM_WB)
  io.reg_write := (wbsel =/= WB_NONE)
  when (io.wb_en && io.wb_rd =/= 0.U) {
    regfile(io.wb_rd) := io.wb_data
  }

  // -------- 异常处理 --------
  val trap = Module(new EBreak)
  // 定义异常编码规则
  // 0: EBREAK, 1: 全零指令, 2: 其他E指令, 3: 未实现指令
  val impl_inst = Instructions.IMPLEMENTED.filterNot(inst =>
    inst == Instructions.E || inst == Instructions.EBREAK
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
  trap.io.trap := ~reset.asBool && is_unimpl
  trap.io.code := exc_code
  // halt 信号
  io.halt := ~reset.asBool && is_unimpl
}

// ---------------------------
// EX 模块
// ---------------------------
class EX extends Module {
  import Parameters._
  val io = IO(new Bundle {
    val pc    = Input(UInt(32.W))
    val op1   = Input(UInt(32.W))
    val op2   = Input(UInt(32.W))
    val exsel = Input(UInt(EX_SEL_LEN.W))

    val exout  = Output(UInt(32.W))
    val pcn = Output(UInt(32.W))
  })

  val jumpen = (io.exsel === EX_JALR)
  // -------- ALU --------
  io.exout := Mux(jumpen, io.pc + 4.U, io.op1 + io.op2)
  // -------- JUMP --------
  io.pcn := Mux(jumpen, io.exout & ~1.U(32.W), io.pc + 4.U)
}

// ---------------------------
// MiniRV CPU（单周期）
// ---------------------------
class MiniRV extends Module {
  import Instructions._
  import Parameters._
  val io = IO(new Bundle {
    val pc   = Output(UInt(32.W))
    val inst = Input(UInt(32.W))

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
  io.pc := ifStage.io.pc

  // ID
  idStage.io.inst := io.inst

  // EX
  exStage.io.pc    := ifStage.io.pc
  exStage.io.op1   := idStage.io.op1
  exStage.io.op2   := idStage.io.op2
  exStage.io.exsel := idStage.io.exsel

  // Memory
  io.mem_addr  := exStage.io.exout
  io.mem_wdata := idStage.io.op2
  io.mem_we    := idStage.io.memWen
  io.mem_mask  := Mux(
    idStage.io.memBen,
    "b0001".U, "b1111".U
  )

  // Write Back
  val wb_data = Mux(
    idStage.io.memRen,
    io.mem_rdata, exStage.io.exout
  )

  idStage.io.wb_en   := idStage.io.reg_write
  idStage.io.wb_rd   := idStage.io.rd_addr
  idStage.io.wb_data := wb_data

  // PC update
  ifStage.io.pcn := exStage.io.pcn
  when (idStage.io.halt) {ifStage.io.pcn := ifStage.io.pc}
}

// ---------------------------
// MiniRV SOC：自包含 CPU + ROM + RAM
// ---------------------------
class MiniRVSOC extends Module {
  val io = IO(new Bundle {
    val pc   = Output(UInt(32.W))
    val inst = Output(UInt(32.W))
  })

  val cpu = Module(new MiniRV)
  val rom = Module(new ROM_DPI)
  val ram = Module(new RAM_DPI)

  // 指令取值
  rom.io.addr := cpu.io.pc
  cpu.io.inst := rom.io.data

  // 数据访存
  ram.io.we    := cpu.io.mem_we
  ram.io.addr  := cpu.io.mem_addr
  ram.io.mask  := cpu.io.mem_mask
  ram.io.wdata := cpu.io.mem_wdata
  cpu.io.mem_rdata := ram.io.rdata

  // 输出
  io.pc   := cpu.io.pc
  io.inst := cpu.io.inst
}
