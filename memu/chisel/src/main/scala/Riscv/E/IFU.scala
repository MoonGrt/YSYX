package soc.riscv.e

import chisel3._
import chisel3.util._
import soc.util._
import soc.riscv.Constants.Riscv32E._
import soc.riscv.Parameters.Riscv32E._
import soc.perip.mem.InstBus

// ----------------------------------
// IFU: Instruction Fetch
// ----------------------------------
class IFUOut extends Bundle{
  val pc   = UInt(DataWidth.W)
  val inst = UInt(DataWidth.W)
}
class IFU(resetPc: BigInt = 0x80000000L) extends Module {
  require(resetPc >= 0 && resetPc < (BigInt(1) << DataWidth),
    s"resetPc 0x${resetPc.toString(16)} does not fit in $DataWidth bits")
  val io = IO(new Bundle {
    val ibus = new InstBus(DataWidth)
    val in   = Flipped(Decoupled(new BROut))
    val out  = Decoupled(new IFUOut)
  })
  // -----------------------------------------------
  // -------------------- State --------------------
  // -----------------------------------------------
  private val sIdle :: sWait :: sHold :: Nil = Enum(3)
  val state = RegInit(sIdle)
  val responseInst = RegInit(0.U(DataWidth.W))
  val requestPc = RegInit(resetPc.U(DataWidth.W))

  io.ibus.req.valid := !reset.asBool && (state === sIdle)
  io.ibus.resp.ready := state === sWait
  io.in.ready := io.out.fire
  io.out.valid := (state === sWait && io.ibus.resp.valid) || state === sHold
  // -----------------------------------------------
  // -------------------- Input --------------------
  // -----------------------------------------------
  val inst = Mux(state === sHold, responseInst, io.ibus.resp.bits.data)
  val bren = io.in.valid && io.in.bits.bren
  val braddr = io.in.bits.braddr
  // -----------------------------------------------
  // -------------------- Logic --------------------
  // -----------------------------------------------
  val pc  = RegInit(resetPc.U(DataWidth.W))

  when(io.ibus.req.fire) {
    requestPc := pc
    state := sWait
  }
  when(state === sWait && io.ibus.resp.fire) {
    when(io.out.ready) {
      pc := Mux(bren, braddr, pc + 4.U)
      state := sIdle
    }.otherwise {
      responseInst := io.ibus.resp.bits.data
      state := sHold
    }
  }
  when(state === sHold && io.out.fire) {
    pc := Mux(bren, braddr, pc + 4.U)
    state := sIdle
  }
  // -------- Inst Bus --------
  io.ibus.req.bits.addr := pc
  // -----------------------------------------------
  // -------------------- Output -------------------
  // -----------------------------------------------
  io.out.bits.pc := requestPc
  io.out.bits.inst := inst
  // -----------------------------------------------
  // -------------------- DiffTest -----------------
  // -----------------------------------------------
  val started = RegEnable(true.B, false.B, io.out.fire)
  val diffen = (started === true.B) && io.out.fire
  val diffpc = Module(new DpiDiffPCBB)
  diffpc.io.clk  := clock
  diffpc.io.en   := diffen
  diffpc.io.pc   := requestPc
  diffpc.io.npc  := Mux(bren, braddr, pc + 4.U)
  diffpc.io.inst := inst
}
