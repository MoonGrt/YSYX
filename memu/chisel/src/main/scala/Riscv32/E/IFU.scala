package riscv.e

import chisel3._
import chisel3.util._
import riscv.util._
import riscv.Constants._

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
  private val sIdle :: sWait :: Nil = Enum(2)
  val state = RegInit(sIdle)
  state := MuxLookup(state, sIdle)(List(
    sIdle -> Mux(io.ibus.req.fire, sWait, sIdle),
    sWait -> Mux(io.out.fire, sIdle, sWait)
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
  val npc = Mux(io.out.fire, Mux(bren, braddr, pc + 4.U), pc)
  pc := npc
  dontTouch(npc)
  // -------- Inst Bus --------
  io.ibus.req.bits.addr := pc
  // -----------------------------------------------
  // -------------------- Output -------------------
  // -----------------------------------------------
  val pc_reg = Reg(UInt(DataWidth.W))
  when (io.ibus.req.fire) {
    pc_reg := pc
  }
  io.out.bits.pc := pc_reg
  io.out.bits.inst := inst
  // -----------------------------------------------
  // -------------------- DiffTest -----------------
  // -----------------------------------------------
  val started = RegInit(false.B)
  when (io.out.fire) {
    started := true.B
  }
  val diffen = (started === true.B) && io.out.fire
  val diffpc = Module(new DiffPC)
  diffpc.io.clk  := clock
  diffpc.io.en   := diffen
  diffpc.io.pc   := pc_reg
  diffpc.io.npc  := npc
  diffpc.io.inst := inst
}
