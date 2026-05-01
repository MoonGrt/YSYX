package riscv.e

import chisel3._
import chisel3.util._
import riscv.Constants._
import riscv.util._

// ----------------------------------
// IFU: Instruction Fetch
// ----------------------------------
class IFUOut extends Bundle{
  val pc   = UInt(DataWidth.W)
  val inst = UInt(DataWidth.W)
}
class IFU extends Module {
  val io = IO(new Bundle {
    val ibus = new InstBus
    val in   = Flipped(Decoupled(new BROut))
    val out  = Decoupled(new IFUOut)
  })
  // -----------------------------------------------
  // -------------------- State --------------------
  // -----------------------------------------------
  val started = RegNext(!reset.asBool)
  private val sIdle :: sWait :: Nil = Enum(2)
  val state = RegInit(sIdle)
  state := MuxLookup(state, sIdle)(List(
    sIdle -> Mux(io.ibus.req.fire, sWait, sIdle),
    sWait -> Mux(io.ibus.resp.fire, sIdle, sWait)
  ))
  io.ibus.req.valid := !reset.asBool && (state === sIdle)
  io.ibus.resp.ready := true.B
  io.in.ready := !reset.asBool && (state === sIdle)
  io.out.valid := io.ibus.resp.fire
  // -----------------------------------------------
  // -------------------- Input --------------------
  // -----------------------------------------------
  val inst = io.ibus.resp.bits.data
  val bren = io.in.bits.bren
  val braddr = io.in.bits.braddr
  // -----------------------------------------------
  // -------------------- Logic --------------------
  // -----------------------------------------------
  val pc  = RegInit("h80000000".U)
  val npc = Mux(io.ibus.req.fire , Mux(bren, braddr, pc + 4.U), pc)
  pc := npc
  // -------- Inst Bus --------
  io.ibus.req.bits.addr := pc
  // -----------------------------------------------
  // -------------------- Output -------------------
  // -----------------------------------------------
  io.out.bits.pc := RegNext(pc)
  io.out.bits.inst := inst
  // -----------------------------------------------
  // -------------------- DiffTest -----------------
  // -----------------------------------------------
  val diffpc = Module(new DiffPC)
  diffpc.io.pc   := pc
  diffpc.io.npc  := npc
  diffpc.io.inst := inst
}
