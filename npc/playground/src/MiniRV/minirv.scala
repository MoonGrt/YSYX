import chisel3._
import chisel3.util._

// ---------------------------
// IF 模块：Instruction Fetch
// ---------------------------
class IF extends Module {
  val io = IO(new Bundle {
    val pc_next = Input(UInt(32.W))    // 下一个 PC
    val instr   = Output(UInt(32.W))   // 当前指令
    val pc_out  = Output(UInt(32.W))   // 当前 PC 输出
  })

  // PC 寄存器
  val pc = RegInit(0.U(32.W))
  pc := io.pc_next

  // 简单指令存储器 1K x 32bit
  val imem = Mem(1024, UInt(32.W))
  io.instr := imem(pc >> 2)  // 通过 PC 访问指令
  io.pc_out := pc
}

// ---------------------------
// ID 模块：Instruction Decode + GPR
// ---------------------------
class ID extends Module {
  val io = IO(new Bundle {
    val instr     = Input(UInt(32.W))  // 当前指令
    val pc        = Input(UInt(32.W))  // 当前 PC
    val rs1_data  = Output(UInt(32.W)) // 源寄存器 1 数据
    val rs2_data  = Output(UInt(32.W)) // 源寄存器 2 数据
    val rd_addr   = Output(UInt(5.W))  // 目的寄存器地址
    val imm       = Output(UInt(32.W)) // 立即数
    val alu_op    = Output(UInt(4.W))  // ALU 操作
    val mem_read  = Output(Bool())     // 内存读信号
    val mem_write = Output(Bool())     // 内存写信号
    val reg_write = Output(Bool())     // 写回寄存器信号
    val jalr      = Output(Bool())     // 是否 jalr 指令
  })

  // 通用寄存器堆 32x32
  val regfile = RegInit(VecInit(Seq.fill(32)(0.U(32.W))))

  // 指令字段解析
  val opcode = io.instr(6,0)
  val rd     = io.instr(11,7)
  val funct3 = io.instr(14,12)
  val rs1    = io.instr(19,15)
  val rs2    = io.instr(24,20)
  val funct7 = io.instr(31,25)

  // 读取寄存器值
  io.rs1_data := regfile(rs1)
  io.rs2_data := regfile(rs2)
  io.rd_addr  := rd

  // 立即数生成
  val imm_i = io.instr(31,20)          // I 型立即数
  val imm_u = io.instr(31,12) << 12    // U 型立即数
  val imm_s = Cat(io.instr(31,25), io.instr(11,7))  // S 型立即数

  // 根据 opcode 选择立即数
  io.imm := MuxLookup(opcode, 0.U, Seq(
    "b0010011".U -> imm_i,  // addi
    "b0110111".U -> imm_u,  // lui
    "b0000011".U -> imm_i,  // lw, lbu
    "b0100011".U -> imm_s,  // sw, sb
    "b1100111".U -> imm_i   // jalr
  ))

  // ALU 操作码：0=add, 1=addi/lw/sw/lbu/sb, 2=lui
  io.alu_op := MuxLookup(opcode, 0.U, Seq(
    "b0110011".U -> 0.U, // add
    "b0010011".U -> 1.U, // addi
    "b0110111".U -> 2.U, // lui
    "b0000011".U -> 1.U, // lw, lbu
    "b0100011".U -> 1.U, // sw, sb
    "b1100111".U -> 1.U  // jalr
  ))

  // 内存读写信号
  io.mem_read  := (opcode === "b0000011".U)
  io.mem_write := (opcode === "b0100011".U)
  io.reg_write := (opcode === "b0110011".U || opcode === "b0010011".U ||
                   opcode === "b0000011".U || opcode === "b0110111".U || 
                   opcode === "b1100111".U)

  io.jalr := (opcode === "b1100111".U)
}

// ---------------------------
// EX 模块：Execute/ALU
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
    val pc_next = Output(UInt(32.W)) // jalr 更新 PC
  })

  // 简单 ALU
  io.alu_out := MuxLookup(io.alu_op, 0.U, Seq(
    0.U -> (io.rs1 + io.rs2), // add
    1.U -> (io.rs1 + io.imm), // addi, lw, sw, lbu, sb, jalr
    2.U -> io.imm             // lui
  ))

  // 内存地址计算
  io.mem_addr := io.rs1 + io.imm

  // jalr 指令 PC 更新
  io.pc_next := Mux(io.jalr, (io.rs1 + io.imm) & ~1.U(32.W), io.pc + 4.U)
}

// ---------------------------
// Mini-RV 顶层 CPU 模块
// ---------------------------
class top extends Module {
  val io = IO(new Bundle {
    val mem_rdata = Input(UInt(32.W))  // 从内存读到的数据
    val mem_wdata = Output(UInt(32.W)) // 写内存数据
    val mem_addr  = Output(UInt(32.W)) // 内存地址
    val mem_we    = Output(Bool())     // 写使能
  })

  // IF / ID / EX 模块实例化
  val ifStage = Module(new IF)
  val idStage = Module(new ID)
  val exStage = Module(new EX)

  // ---------------------------
  // IF <-> ID
  // ---------------------------
  idStage.io.instr := ifStage.io.instr
  idStage.io.pc    := ifStage.io.pc_out

  // ---------------------------
  // ID <-> EX
  // ---------------------------
  exStage.io.rs1    := idStage.io.rs1_data
  exStage.io.rs2    := idStage.io.rs2_data
  exStage.io.imm    := idStage.io.imm
  exStage.io.alu_op := idStage.io.alu_op
  exStage.io.jalr   := idStage.io.jalr
  exStage.io.pc     := ifStage.io.pc_out

  // ---------------------------
  // Memory 接口
  // ---------------------------
  io.mem_addr  := exStage.io.mem_addr
  io.mem_wdata := idStage.io.rs2_data
  io.mem_we    := idStage.io.mem_write

  // ---------------------------
  // PC 更新
  // ---------------------------
  ifStage.io.pc_next := exStage.io.pc_next
}
