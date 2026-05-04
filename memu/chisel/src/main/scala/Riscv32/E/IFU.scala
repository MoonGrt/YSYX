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
  private val sIdle :: sWait :: sLoad :: Nil = Enum(3)
  val state = RegInit(sIdle)
  state := MuxLookup(state, sIdle)(List(
    sIdle -> Mux(io.ibus.req.fire, sWait, sIdle),
    sWait -> Mux(io.out.valid, sLoad, sWait),
    sLoad -> Mux(io.out.ready, sIdle, sLoad),
  ))
  io.ibus.req.valid := (state === sIdle)
  io.ibus.resp.ready := io.out.ready
  io.in.ready := (state === sIdle)
  io.out.valid := io.ibus.resp.valid
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
  when (io.out.valid) {
    pc := Mux(bren, braddr, pc + 4.U)
  }
  // -------- Inst Bus --------
  io.ibus.req.bits.addr := pc
  // -----------------------------------------------
  // -------------------- Output -------------------
  // -----------------------------------------------
  val pc_reg = RegEnable(pc, io.ibus.req.valid)
  io.out.bits.pc := pc_reg
  io.out.bits.inst := inst
  // -----------------------------------------------
  // -------------------- DiffTest -----------------
  // -----------------------------------------------
  val started = RegInit(false.B)
  when (io.out.valid) {
    started := true.B
  }
  val diffen = (started === true.B) && io.ibus.req.valid
  val diffpc = Module(new DiffPC)
  diffpc.io.clk  := clock
  diffpc.io.en   := diffen
  diffpc.io.pc   := pc
  diffpc.io.npc  := Mux(bren, braddr, pc + 4.U)
  diffpc.io.inst := RegNext(inst)
}
