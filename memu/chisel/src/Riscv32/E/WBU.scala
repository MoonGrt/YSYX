package riscv.e

import chisel3._
import chisel3.util._
import riscv.Constants._
import riscv.Constants.Riscv32E._

// ----------------------------------
// WBU: Write Back Unit
// ----------------------------------
class WBUOut extends Bundle{
  val gprWen   = Bool()
  val gprAddr = UInt(log2Ceil(GPRNum).W)
  val gprData = UInt(DataWidth.W)
}
class WBU extends Module {
  val io = IO(new Bundle {
    val in  = Flipped(Decoupled(new LSUOut))
    val out = Decoupled(new WBUOut)
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
  val wbSel   = io.in.bits.wbSel
  val wbrd    = io.in.bits.wbrd
  val pc      = io.in.bits.pc
  val csrData = io.in.bits.csrData
  val aluData = io.in.bits.aluData
  val memData = io.in.bits.memData
  // -----------------------------------------------
  // -------------------- Logic --------------------
  // -----------------------------------------------
  val gprData = MuxLookup(wbSel, 0.U)(Seq(
    WB.PC  -> (pc + 4.U),
    WB.EX  -> aluData,
    WB.LS  -> memData,
    WB.CSR -> csrData,
  ))
  val gprWen   = (wbSel =/= WB.NONE) && (wbrd =/= 0.U)
  val gprAddr = wbrd
  // -----------------------------------------------
  // -------------------- Output -------------------
  // -----------------------------------------------
  io.out.valid       := io.out.ready
  io.out.bits.gprWen   := gprWen
  io.out.bits.gprAddr := gprAddr
  io.out.bits.gprData := gprData
}
