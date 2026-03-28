package riscv.e

import chisel3._
import chisel3.util._
import riscv.Constants._
import riscv.Constants.Riscv32E._

// ----------------------------------
// EXU 模块: Execution Unit
// ----------------------------------
class EXU extends Module {
  val io = IO(new Bundle {
    val exsel  = Input(EX())
    val pc     = Input(UInt(DataWidth.W))
    val op1    = Input(UInt(DataWidth.W))
    val op2    = Input(UInt(DataWidth.W))
    val immsb  = Input(UInt(DataWidth.W))
    val aluout = Output(UInt(DataWidth.W))
    val bren   = Output(Bool())
    val braddr = Output(UInt(DataWidth.W))
  })
  // -------- ALU --------
  io.aluout := MuxCase(0.U(DataWidth.W), Seq(
    (io.exsel === EX.ADD ) -> (io.op1 + io.op2),
    (io.exsel === EX.SUB ) -> (io.op1 - io.op2),
    (io.exsel === EX.AND ) -> (io.op1 & io.op2),
    (io.exsel === EX.OR  ) -> (io.op1 | io.op2),
    (io.exsel === EX.XOR ) -> (io.op1 ^ io.op2),
    (io.exsel === EX.SLL ) -> (io.op1 << io.op2(4,0)),
    (io.exsel === EX.SRL ) -> (io.op1 >> io.op2(4,0)),
    (io.exsel === EX.SRA ) -> (io.op1.asSInt >> io.op2(4,0)).asUInt,
    (io.exsel === EX.SLT ) -> (io.op1.asSInt < io.op2.asSInt).asUInt,
    (io.exsel === EX.SLTU) -> (io.op1 < io.op2),
  ))
  // -------- Branch --------
  io.bren := MuxCase(false.B, Seq(
    (io.exsel === EX.JAL ) ->  true.B,
    (io.exsel === EX.CSR ) ->  true.B,
    (io.exsel === EX.BEQ ) ->  (io.op1 === io.op2),
    (io.exsel === EX.BNE ) -> !(io.op1 === io.op2),
    (io.exsel === EX.BLT ) ->  (io.op1.asSInt < io.op2.asSInt),
    (io.exsel === EX.BGE ) -> !(io.op1.asSInt < io.op2.asSInt),
    (io.exsel === EX.BLTU) ->  (io.op1 < io.op2),
    (io.exsel === EX.BGEU) -> !(io.op1 < io.op2),
  ))
  io.braddr := MuxCase(io.pc + io.immsb, Seq(
    (io.exsel === EX.JAL) -> (io.op1 + io.op2),
    (io.exsel === EX.CSR) -> (io.op2),  // mtvec
  ))
}
