package riscv.e

import chisel3._
import chisel3.util._
import riscv.Constants._
import riscv.Constants.Riscv32E._

// ----------------------------------
// WBU: Write Back Unit
// ----------------------------------
class WBUOut extends Bundle{
  val gprWen  = Bool()
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
  val gprSel  = io.in.bits.gprSel
  val gprAddr = io.in.bits.gprAddr
  val pc      = io.in.bits.pc
  val csrData = io.in.bits.csrData
  val aluData = io.in.bits.aluData
  val memData = io.in.bits.memData
  // -----------------------------------------------
  // -------------------- Logic --------------------
  // -----------------------------------------------
  val gprWen  = (gprSel =/= GPR.NONE) && (gprAddr =/= 0.U)
  val gprData = MuxLookup(gprSel, 0.U)(Seq(
    GPR.PC  -> (pc + 4.U),
    GPR.EX  -> aluData,
    GPR.LS  -> memData,
    GPR.CSR -> csrData,
  ))
  // -----------------------------------------------
  // -------------------- Output -------------------
  // -----------------------------------------------
  io.out.valid        := io.out.ready
  io.out.bits.gprWen  := gprWen
  io.out.bits.gprAddr := gprAddr
  io.out.bits.gprData := gprData
}
