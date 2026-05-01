package riscv.e

import chisel3._
import chisel3.util._
import riscv.Constants._
import riscv.Constants.Riscv32E._

// ----------------------------------
// EXU: Execution Unit
// ----------------------------------
class EXUOut extends Bundle{
  val lsSel   = LS()
  val gprSel  = GPR()
  val gprAddr = UInt(log2Ceil(GPRNum).W)
  val pc      = UInt(DataWidth.W)
  val RS2     = UInt(DataWidth.W)
  val csrData = UInt(DataWidth.W)
  val aluData = UInt(DataWidth.W)
}
class BROut extends Bundle{
  val bren   = Bool()
  val braddr = UInt(DataWidth.W)
}
class EXU extends Module {
  val io = IO(new Bundle {
    val in  = Flipped(Decoupled(new IDUOut))
    val out = Decoupled(new EXUOut)
    val br  = Decoupled(new BROut)
  })
  // -----------------------------------------------
  // -------------------- State --------------------
  // -----------------------------------------------
  // private val sIdle :: sWait :: Nil = Enum(2)
  // val state = RegInit(sIdle)
  // state := MuxLookup(state, sIdle)(List(
  //   sIdle -> Mux(io.in.fire, sWait, sIdle),
  //   sWait -> Mux(io.out.fire, sIdle, sWait)
  // ))
  io.in.ready := true.B
  io.out.valid := io.in.fire
  // -----------------------------------------------
  // -------------------- Input --------------------
  // -----------------------------------------------
  val exSel = io.in.bits.exSel
  val pc    = io.in.bits.pc
  val op1   = io.in.bits.op1
  val op2   = io.in.bits.op2
  val immsb = io.in.bits.immsb
  // -----------------------------------------------
  // -------------------- Logic --------------------
  // -----------------------------------------------
  // ALU
  val aluout = MuxCase(0.U(DataWidth.W), Seq(
    (exSel === EX.ADD ) -> (op1 + op2),
    (exSel === EX.SUB ) -> (op1 - op2),
    (exSel === EX.AND ) -> (op1 & op2),
    (exSel === EX.OR  ) -> (op1 | op2),
    (exSel === EX.XOR ) -> (op1 ^ op2),
    (exSel === EX.SLL ) -> (op1 << op2(4,0)),
    (exSel === EX.SRL ) -> (op1 >> op2(4,0)),
    (exSel === EX.SRA ) -> (op1.asSInt >> op2(4,0)).asUInt,
    (exSel === EX.SLT ) -> (op1.asSInt < op2.asSInt).asUInt,
    (exSel === EX.SLTU) -> (op1 < op2),
  ))
  // Branch
  val bren = MuxCase(false.B, Seq(
    (exSel === EX.JAL ) ->  true.B,
    (exSel === EX.CSR ) ->  true.B,
    (exSel === EX.BEQ ) ->  (op1 === op2),
    (exSel === EX.BNE ) -> !(op1 === op2),
    (exSel === EX.BLT ) ->  (op1.asSInt < op2.asSInt),
    (exSel === EX.BGE ) -> !(op1.asSInt < op2.asSInt),
    (exSel === EX.BLTU) ->  (op1 < op2),
    (exSel === EX.BGEU) -> !(op1 < op2),
  ))
  val braddr = MuxCase(pc + immsb, Seq(
    (exSel === EX.JAL) -> (op1 + op2),
    (exSel === EX.CSR) -> (op2),  // mtvec
  ))
  // -----------------------------------------------
  // -------------------- Output -------------------
  // -----------------------------------------------
  io.out.bits.aluData := aluout
  io.br.valid         := io.br.ready
  io.br.bits.bren     := bren
  io.br.bits.braddr   := braddr
  // pass through
  io.out.bits.lsSel   := io.in.bits.lsSel
  io.out.bits.gprSel  := io.in.bits.gprSel
  io.out.bits.gprAddr := io.in.bits.gprAddr
  io.out.bits.pc      := io.in.bits.pc
  io.out.bits.RS2     := io.in.bits.RS2
  io.out.bits.csrData := io.in.bits.csrData
}
