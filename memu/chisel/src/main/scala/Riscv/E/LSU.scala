package soc.riscv.e

import chisel3._
import chisel3.util._
import soc.riscv.Constants.Riscv32E._
import soc.riscv.Parameters.Riscv32E._
import soc.perip.mem.DataBus

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
    val dbus = new DataBus(DataWidth)
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
  val ren = lsSel.isOneOf(LS.RW, LS.RH, LS.RB, LS.RHU, LS.RBU)
  val wen = lsSel.isOneOf(LS.WW, LS.WH, LS.WB)
  dontTouch(ren)
  dontTouch(wen)
  io.dbus.req.bits.ren := io.in.valid && ren
  io.dbus.req.bits.wen := io.in.valid && wen
  val dbus_req = io.dbus.req.bits.ren || io.dbus.req.bits.wen
  // -----------------------------------------------
  // -------------------- State --------------------
  // -----------------------------------------------
  private val sIdle :: sWait :: Nil = Enum(2)
  val state = RegInit(sIdle)
  dontTouch(io.in.ready)
  io.dbus.req.valid := !reset.asBool && (state === sIdle) && dbus_req
  io.dbus.resp.ready := (state === sWait) && io.out.ready
  io.in.ready :=
    Mux(state === sIdle, !dbus_req && io.out.ready,
      io.dbus.resp.valid && io.out.ready)
  io.out.valid :=
    Mux(state === sIdle, io.in.valid && !dbus_req,
      io.dbus.resp.valid)

  when(state === sIdle && io.dbus.req.fire) {
    state := sWait
  }
  when(state === sWait && io.dbus.resp.fire) {
    state := sIdle
  }
  // -----------------------------------------------
  // -------------------- Logic --------------------
  // -----------------------------------------------
  // Address Align
  val memAddrAlign = Cat(memAddr(31,2), 0.U(2.W))
  val offset = memAddr(1,0)  // byte offset
  val readOffset = RegEnable(offset, 0.U, io.dbus.req.fire && ren)
  val responseOffset = Mux(state === sWait, readOffset, offset)
  dontTouch(offset)
  val mask = MuxLookup(lsSel, "b0000".U)(Seq(
    LS.WB -> (1.U << offset),  // 1 byte
    LS.WH -> (3.U << offset),  // 2 bytes
    LS.WW -> "b1111".U         // 4 bytes
  ))
  val size = MuxLookup(lsSel, 2.U)(Seq(
    LS.RB  -> 0.U, LS.RBU -> 0.U, LS.WB -> 0.U,
    LS.RH  -> 1.U, LS.RHU -> 1.U, LS.WH -> 1.U,
    LS.RW  -> 2.U, LS.WW  -> 2.U
  ))
  // Write Data Align
  val wdataShift = io.in.bits.RS2 << (offset << 3)
  // Read Data Align
  val rdataShift = memRdata >> (responseOffset << 3)
  val memData = MuxLookup(lsSel, 0.U)(Seq(
    LS.RW  -> memRdata,
    LS.RB  -> Cat(Fill(24, rdataShift(7)),  rdataShift(7,0)),
    LS.RH  -> Cat(Fill(16, rdataShift(15)), rdataShift(15,0)),
    LS.RBU -> Cat(0.U(24.W), rdataShift(7,0)),
    LS.RHU -> Cat(0.U(16.W), rdataShift(15,0)),
  ))
  // -------- Data Bus --------
  io.dbus.req.bits.mask  := mask
  io.dbus.req.bits.size  := size
  val isUart = memAddr(31, 12) === "h10000".U
  io.dbus.req.bits.addr  := Mux(isUart, memAddr, memAddrAlign)
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
