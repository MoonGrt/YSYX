package riscv.e

import chisel3._
import chisel3.util._
import riscv.Constants._
import riscv.Constants.Riscv32E._

// ----------------------------------
// LSU: Load/Store Unit
// ----------------------------------
class LSUOut extends Bundle{
  val gprSel  = GPR()
  val gprAddr = UInt(log2Ceil(GPRNum).W)
  val pc      = UInt(DataWidth.W)
  val csrData = UInt(DataWidth.W)
  val aluData = UInt(DataWidth.W)
  val memData = UInt(DataWidth.W)
}
class LSU extends Module {
  val io = IO(new Bundle {
    val dbus = new DataBus
    val in   = Flipped(Decoupled(new EXUOut))
    val out  = Decoupled(new LSUOut)
  })
  // -----------------------------------------------
  // -------------------- Input --------------------
  // -----------------------------------------------
  val lsSel    = io.in.bits.lsSel
  val memAddr  = io.in.bits.aluData
  val memRdata = io.dbus.resp.bits.rdata
  // -------- Data Bus --------
  io.dbus.req.bits.ren := !reset.asBool && lsSel.isOneOf(LS.RW, LS.RH, LS.RB, LS.RHU, LS.RBU)
  io.dbus.req.bits.wen := !reset.asBool && lsSel.isOneOf(LS.WW, LS.WH, LS.WB)
  val dbus_req = io.dbus.req.bits.ren || io.dbus.req.bits.wen
  // -----------------------------------------------
  // -------------------- State --------------------
  // -----------------------------------------------
  private val sIdle :: sWait :: Nil = Enum(2)
  val state = RegInit(sIdle)
  state := MuxLookup(state, sIdle)(List(
    sIdle -> Mux(io.dbus.req.fire, sWait, sIdle),
    sWait -> Mux(io.out.fire, sIdle, sWait)
  ))
  io.dbus.req.valid := !reset.asBool && (state === sIdle) && dbus_req
  io.dbus.resp.ready := true.B
  io.in.ready := !reset.asBool && (state === sIdle)
  io.out.valid := io.dbus.resp.fire || (!dbus_req && io.in.fire)
  // -----------------------------------------------
  // -------------------- Logic --------------------
  // -----------------------------------------------
  // Address Align
  val memAddrAlign = Cat(memAddr(31,2), 0.U(2.W))  // word aligned
  val offset = memAddr(1,0)  // byte offset
  val mask = MuxLookup(lsSel, "b0000".U)(Seq(
    LS.WB -> (1.U << offset),  // 1 byte
    LS.WH -> (3.U << offset),  // 2 bytes
    LS.WW -> "b1111".U         // 4 bytes
  ))
  // Write Data Align
  val wdataShift = io.in.bits.RS2 << (offset << 3)
  // Read Data Align
  val rdataShift = memRdata >> (offset << 3)
  val memData = MuxLookup(lsSel, 0.U)(Seq(
    LS.RW  -> rdataShift,
    LS.RB  -> Cat(Fill(24, rdataShift(7)),  rdataShift(7,0)),
    LS.RH  -> Cat(Fill(16, rdataShift(15)), rdataShift(15,0)),
    LS.RBU -> Cat(0.U(24.W), rdataShift(7,0)),
    LS.RHU -> Cat(0.U(16.W), rdataShift(15,0)),
  ))
  // -------- Data Bus --------
  io.dbus.req.bits.mask  := mask
  io.dbus.req.bits.addr  := memAddrAlign
  io.dbus.req.bits.wdata := wdataShift
  // -----------------------------------------------
  // -------------------- Output -------------------
  // -----------------------------------------------
  io.out.bits.memData := memData
  // pass through
  io.out.bits.gprSel  := io.in.bits.gprSel
  io.out.bits.gprAddr := io.in.bits.gprAddr
  io.out.bits.pc      := io.in.bits.pc
  io.out.bits.csrData := io.in.bits.csrData
  io.out.bits.aluData := io.in.bits.aluData
}
