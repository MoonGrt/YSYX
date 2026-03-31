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
    val in  = Flipped(Decoupled(new BROut))
    val bus = new InstBus
    val out = Decoupled(new IFUOut)
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
  val inst = io.bus.data.bits
  val bren = io.in.bits.bren
  val braddr = io.in.bits.braddr
  // -----------------------------------------------
  // -------------------- Logic --------------------
  // -----------------------------------------------
  val pc  = RegInit("h80000000".U)
  val npc = Mux(io.bus.addr.fire , Mux(bren, braddr, pc + 4.U), pc)
  pc := npc
  // -------- Inst Bus --------
  io.bus.addr.bits := pc
  io.bus.addr.valid := io.bus.addr.ready
  io.bus.data.ready := true.B
  // -----------------------------------------------
  // -------------------- Output -------------------
  // -----------------------------------------------
  io.out.valid := io.out.ready
  io.out.bits.pc := pc
  io.out.bits.inst := inst
  // -----------------------------------------------
  // -------------------- DiffTest -----------------
  // -----------------------------------------------
  val diffpc = Module(new DiffPC)
  diffpc.io.pc   := pc
  diffpc.io.npc  := npc
  diffpc.io.inst := io.out.bits.inst
}
