package riscv.e

import chisel3._
import chisel3.util._
import riscv.Constants._
import riscv.Constants.Riscv32E._

// ----------------------------------
// LSU: Load/Store Unit
// ----------------------------------
class LSUOut extends Bundle{
  val wbSel   = WB()
  val wbrd    = UInt(log2Ceil(GPRNum).W)
  val pc      = UInt(DataWidth.W)
  val csrData = UInt(DataWidth.W)
  val aluData = UInt(DataWidth.W)
  val memData = UInt(DataWidth.W)
}
class LSU extends Module {
  val io = IO(new Bundle {
    val in  = Flipped(Decoupled(new EXUOut))
    val bus = new DataBus
    val out = Decoupled(new LSUOut)
  })
  // -----------------------------------------------
  // -------------------- State --------------------
  // -----------------------------------------------
  // private val sIdle :: sWait :: Nil = Enum(2)
  // val state = RegInit(sIdle)
  // state := MuxLookup(state, sIdle)(List(
  //   sIdle -> Mux(io.bus.addr.fire, sWait, sIdle),
  //   sWait -> Mux(io.out.fire, sIdle, sWait)
  // ))
  // -----------------------------------------------
  // -------------------- Input --------------------
  // -----------------------------------------------
  io.in.ready := true.B
  val lsSel    = io.in.bits.lsSel
  val memRdata = io.bus.memRdata
  // -----------------------------------------------
  // -------------------- Logic --------------------
  // -----------------------------------------------
  // Data Bus
  io.bus.memRen   := !reset.asBool && lsSel.isOneOf(LS.RW, LS.RH, LS.RB, LS.RHU, LS.RBU)
  io.bus.memWen   := !reset.asBool && lsSel.isOneOf(LS.WW, LS.WH, LS.WB)
  io.bus.memLen   := Mux(lsSel.isOneOf(LS.WB, LS.RB, LS.RBU), 1.U,
                     Mux(lsSel.isOneOf(LS.WH, LS.RH, LS.RHU), 2.U, 4.U))
  io.bus.memAddr  := io.in.bits.aluData
  io.bus.memWdata := io.in.bits.RS2
  // Memory Data
  val memData = MuxLookup(lsSel, 0.U)(Seq(
    LS.RW  -> memRdata,
    LS.RB  -> Cat(Fill(24, memRdata( 7)), memRdata( 7,0)),  // LB SIGN Extend
    LS.RH  -> Cat(Fill(16, memRdata(15)), memRdata(15,0)),  // LH SIGN Extend
    LS.RBU -> Cat(0.U(24.W), memRdata( 7,0)),  // LBU Zero Extend
    LS.RHU -> Cat(0.U(16.W), memRdata(15,0)),  // LHU Zero Extend
  ))
  // -----------------------------------------------
  // -------------------- Output -------------------
  // -----------------------------------------------
  io.out.valid        := io.out.ready
  io.out.bits.memData := memData
  // pass through
  io.out.bits.wbSel   := io.in.bits.wbSel
  io.out.bits.wbrd    := io.in.bits.wbrd
  io.out.bits.pc      := io.in.bits.pc
  io.out.bits.csrData := io.in.bits.csrData
  io.out.bits.aluData := io.in.bits.aluData
}
