package soc.perip.clint

import chisel3._
import chisel3.util._
import bus.amba.axi.common._

/**
  * AXI4-Lite CLINT
  *
  * Only implements:
  *   - mtime register (64-bit, read-only)
  *
  * Memory map:
  *   base + 0x0 : mtime low  32bit
  *   base + 0x4 : mtime high 32bit
  *
  * AXI assumptions:
  *   - single beat only
  *   - AXI4-Lite style access
  */
class AXICLINT(p: AxiParams) extends Module {
  val io = IO(new AXI4SlaveBundle(p))

  // ==========================================================================
  // mtime
  // ==========================================================================
  val mtime = RegInit(0.U(64.W))
  // simplest implementation:
  // increment every cycle
  mtime := mtime + 1.U

  // ==========================================================================
  // Write channel
  // ==========================================================================
  //
  // CLINT is read-only currently.
  // We still need to consume write transactions correctly.
  //
  // --------------------------------------------------------------------------
  private val wIdle :: wWaitData :: wWaitAddr :: wResp :: Nil = Enum(4)

  val wState = RegInit(wIdle)
  val awReg = Reg(new AXI4BundleA(p))
  val awFire = io.aw.fire
  val wFire  = io.w.fire
  val bFire  = io.b.fire

  when(awFire) {
    awReg := io.aw.bits
  }

  switch(wState) {
    is(wIdle) {
      when(awFire && wFire) {
        wState := wResp
      }.elsewhen(awFire) {
        wState := wWaitData
      }.elsewhen(wFire) {
        wState := wWaitAddr
      }
    }
    is(wWaitData) {
      when(wFire) {
        wState := wResp
      }
    }
    is(wWaitAddr) {
      when(awFire) {
        wState := wResp
      }
    }
    is(wResp) {
      when(bFire) {
        wState := wIdle
      }
    }
  }

  io.aw.ready := (wState === wIdle) || (wState === wWaitAddr)
  io.w.ready := (wState === wIdle) || (wState === wWaitData)
  io.b.valid := (wState === wResp)
  io.b.bits.id := awReg.id
  io.b.bits.resp := 0.U // OKAY
  io.b.bits.user := 0.U

  // ==========================================================================
  // Read channel
  // ==========================================================================
  private val rIdle :: rResp :: Nil = Enum(2)
  val rState = RegInit(rIdle)
  val arReg = Reg(new AXI4BundleA(p))
  val rDataReg = Reg(UInt(p.dataBits.W))
  val arFire = io.ar.fire
  val rFire  = io.r.fire
  when(arFire) {
    arReg := io.ar.bits
  }

  // --------------------------------------------------------------------------
  // Address decode
  // --------------------------------------------------------------------------
  when(arFire) {
    rDataReg := MuxLookup(io.ar.bits.addr(3, 0), 0.U)(List(
      0x0.U -> mtime(31, 0),
      0x4.U -> mtime(63, 32)
    ))
  }

  // --------------------------------------------------------------------------
  // Read FSM
  // --------------------------------------------------------------------------
  switch(rState) {
    is(rIdle) {
      when(arFire) {
        rState := rResp
      }
    }
    is(rResp) {
      when(rFire) {
        rState := rIdle
      }
    }
  }

  io.ar.ready := (rState === rIdle)
  io.r.valid := (rState === rResp)
  io.r.bits.id := arReg.id
  io.r.bits.data := rDataReg
  io.r.bits.resp := 0.U // OKAY
  io.r.bits.last := true.B
  io.r.bits.user := 0.U
}
