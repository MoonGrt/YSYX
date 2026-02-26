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
    val clk  = Input(Clock())
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
    val halt   = Input(Bool())  // halt 信号
    val jumpen = Input(Bool())  // 跳转使能
    val jump   = Input(UInt(32.W))  // 跳转地址
    val pcn    = Output(UInt(32.W))  // 下一个 PC
    val pc     = Output(UInt(32.W))  // 当前 PC 输出
  })
  val pc = RegInit("h80000000".U(32.W))
  when (io.halt) {
    pc := pc
  }.otherwise {
    when (io.jumpen) {
      pc := io.jump
    }.otherwise {
      pc := io.pcn
    }
  }
  io.pc  := pc
  io.pcn := pc + 4.U(32.W)
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
  val IMM_SEL_LEN = 2
  val IMMN = 0.U(IMM_SEL_LEN.W)
  val IMMI = 1.U(IMM_SEL_LEN.W)
  val IMMS = 2.U(IMM_SEL_LEN.W)
  val IMMU = 3.U(IMM_SEL_LEN.W)

  val EX_SEL_LEN = 1
  val EX_ADD  = 0.U(EX_SEL_LEN.W)
  val EX_JALR = 1.U(EX_SEL_LEN.W)

  val JUMP_SEL_LEN = 1
  val JUMP_NONE = 0.U(JUMP_SEL_LEN.W)
  val JUMP_JALR = 1.U(JUMP_SEL_LEN.W)

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
    val rs1     = Output(UInt(32.W))
    val rs2     = Output(UInt(32.W))
    val imm     = Output(UInt(32.W))
    val immen   = Output(Bool())
    val rd_addr = Output(UInt(5.W))

    val halt   = Output(Bool())
    val jumpen = Output(Bool())
    val memBen = Output(Bool())
    val memRen = Output(Bool())
    val memWen = Output(Bool())
    val regWen = Output(Bool())
  })

  val decoded = ListLookup(
    io.inst,
    List(IMMN, EX_ADD, JUMP_NONE, WB_EX, MEM_WW),
    Array(
      // Load/Store
      LW   -> List(IMMI, EX_ADD, JUMP_NONE, WB_MEM, MEM_RW),  // x[rs1] + sext(imm_i)
      LBU  -> List(IMMI, EX_ADD, JUMP_NONE, WB_MEM, MEM_RB),  // x[rs1] + sext(imm_i)
      SW   -> List(IMMS, EX_ADD, JUMP_NONE, WB_NONE, MEM_WW),  // x[rs1] + sext(imm_s)
      SB   -> List(IMMS, EX_ADD, JUMP_NONE, WB_NONE, MEM_WB),  // x[rs1] + sext(imm_s)
      // Add
      ADD  -> List(IMMN, EX_ADD, JUMP_NONE, WB_EX, MEM_NONE),  // x[rs1] + x[rs2]
      ADDI -> List(IMMI, EX_ADD, JUMP_NONE, WB_EX, MEM_NONE),  // x[rs1] + sext(imm_i)
      // Jump
      JALR -> List(IMMI, EX_ADD, JUMP_JALR, WB_EX, MEM_NONE),  // x[rd] <- PC+4 and (x[rs1]+sext(imm_i))&~1
      // Load immediate
      LUI  -> List(IMMU, EX_ADD, JUMP_NONE, WB_EX, MEM_NONE),  // sext(imm_u[31:12] << 12)
    ),
  )
  val immsel  = decoded(0)
  val exsel   = decoded(1)
  val jumpsel = decoded(2)
  val wbsel   = decoded(3)
  val memsel  = decoded(4)

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

  // -------- EX操作数 --------
  io.rs1 := Mux(io.inst === LUI, 0.U(32.W), regfile(rs1))
  io.rs2 := regfile(rs2)
  io.imm := MuxLookup(immsel, 0.U)(Seq(
    IMMI -> imm_i,
    IMMS -> imm_s,
    IMMU -> imm_u
  ))
  io.immen := (immsel =/= IMMN)

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
  trap.io.clk  := clock
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
    val rs1   = Input(UInt(32.W))
    val rs2   = Input(UInt(32.W))
    val imm   = Input(UInt(32.W))
    val immen = Input(Bool())
    val exsel = Input(UInt(EX_SEL_LEN.W))
    val exout = Output(UInt(32.W))
  })
  // -------- ALU --------
  io.exout := Mux(
    io.immen,
    io.rs1 + io.imm, io.rs1 - io.rs2
  )
}

// ---------------------------
// MiniRV CPU（单周期）
// ---------------------------
class MiniRV extends Module {
  import Instructions._
  import Parameters._
  val io = IO(new Bundle {
    val pc   = Output(UInt(32.W))
    val snpc = Output(UInt(32.W))
    val dnpc = Output(UInt(32.W))
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
  io.snpc := ifStage.io.pcn
  io.dnpc := exStage.io.exout
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
  io.mem_we    := idStage.io.memWen
  io.mem_addr  := exStage.io.exout
  io.mem_wdata := Mux(idStage.io.memBen,
                      idStage.io.rs2 << (exStage.io.exout(1,0) << 3),
                      idStage.io.rs2)
  io.mem_mask  := Mux(idStage.io.memBen,
                     (1.U << exStage.io.exout(1,0)).asUInt,  // LBU/LB mask
                      "b1111".U)  // SW/SW

  // Write Back
  val byte_shift = (exStage.io.exout(1,0) << 3)  // 位移量
  val byte_data = (io.mem_rdata >> byte_shift)(7,0)  // 取目标字节
  val mem_data  = Mux(idStage.io.memBen,
                      Cat(Fill(24, byte_data(7)), byte_data),  // 零扩展到 32 位
                      io.mem_rdata)
  val wb_data  = MuxCase(
    exStage.io.exout,  // 默认EX输出
    Seq(
      idStage.io.memRen -> mem_data,  // Memory read
      idStage.io.jumpen -> ifStage.io.pcn  // Jump
    )
  )

  idStage.io.wb_en   := idStage.io.regWen
  idStage.io.wb_rd   := idStage.io.rd_addr
  idStage.io.wb_data := wb_data
}

// ---------------------------
// MiniRV SOC：自包含 CPU + ROM + RAM
// ---------------------------
class MiniRVSOC extends Module {
  val io = IO(new Bundle {
    val pc   = Output(UInt(32.W))
    val snpc = Output(UInt(32.W))
    val dnpc = Output(UInt(32.W))
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
  io.snpc := cpu.io.snpc
  io.dnpc := cpu.io.dnpc
  io.inst := cpu.io.inst
}
