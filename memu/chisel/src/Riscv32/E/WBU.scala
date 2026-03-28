package riscv.e

import chisel3._
import chisel3.util._
import riscv.Constants._
import riscv.Constants.Riscv32E._

// ----------------------------------
// WBU 模块: Write Back Unit
// ----------------------------------
class WBU extends Module {
  val io = IO(new Bundle {
    val wbsel   = Input(WB())
    val wbrd    = Input(UInt(log2Ceil(GPR_NUM).W))
    val memsel  = Input(MEM())
    val pc      = Input(UInt(DataWidth.W))
    val csr     = Input(UInt(DataWidth.W))
    val exData  = Input(UInt(DataWidth.W))
    val memData = Input(UInt(DataWidth.W))
    val wben    = Output(Bool())
    val wbAddr  = Output(UInt(log2Ceil(GPR_NUM).W))
    val wbData  = Output(UInt(DataWidth.W))
  })
  io.wben   := (io.wbsel =/= WB.NONE) && (io.wbrd =/= 0.U)
  io.wbAddr := io.wbrd
  val memData = MuxLookup(io.memsel, 0.U)(Seq(
    MEM.RW  -> io.memData,  // LW 直接写回
    MEM.RB  -> Cat(Fill(24, io.memData(7)), io.memData(7,0)),  // LB 符号扩展
    MEM.RH  -> Cat(Fill(16, io.memData(15)), io.memData(15,0)),  // LH 符号扩展
    MEM.RBU -> Cat(0.U(24.W), io.memData(7,0)),  // LBU 零扩展
    MEM.RHU -> Cat(0.U(16.W), io.memData(15,0)),  // LHU 零扩展
  ))
  io.wbData := MuxLookup(io.wbsel, 0.U)(Seq(
    WB.PC  -> (io.pc + 4.U),
    WB.EX  -> io.exData,
    WB.MEM -> memData,
    WB.CSR -> io.csr,
  ))
}
