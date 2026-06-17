package soc.perip.uart

import chisel3._
import chisel3.util._
import soc.util._
import bus.amba.axi.common._

class AXIUART(p: AxiParams) extends Module {
  val io = IO(new AXI4SlaveBundle(p))
  val uart = Module(new UART())

  // --------------------------------------------------------------------------
  // Write FSM
  // --------------------------------------------------------------------------
  private val sIdle :: sWaitData :: sWaitAddr :: sWrite :: sResp :: Nil = Enum(5)
  val state = RegInit(sIdle)

  // --------------------------------------------------------------------------
  // Registers for captured AXI payload
  // --------------------------------------------------------------------------
  val awReg = Reg(new AXI4BundleA(p))
  val wReg  = Reg(new AXI4BundleW(p))
  // Handshake detection
  val awFire = io.aw.fire
  val wFire  = io.w.fire
  val bFire  = io.b.fire
  // Capture address channel
  when(awFire) {
    awReg := io.aw.bits
  }
  // Capture write data channel
  when(wFire) {
    wReg := io.w.bits
  }

  // --------------------------------------------------------------------------
  // FSM transition
  // --------------------------------------------------------------------------
  switch(state) {
    is(sIdle) {
      when(awFire && wFire) {
        state := sWrite
      }.elsewhen(awFire) {
        state := sWaitData
      }.elsewhen(wFire) {
        state := sWaitAddr
      }
    }
    is(sWaitData) {
      when(wFire) {
        state := sWrite
      }
    }
    is(sWaitAddr) {
      when(awFire) {
        state := sWrite
      }
    }
    is(sWrite) {
      state := sResp
    }
    is(sResp) {
      when(bFire) {
        state := sIdle
      }
    }
  }

  // --------------------------------------------------------------------------
  // AXI write address channel
  // --------------------------------------------------------------------------
  io.aw.ready := (state === sIdle) || (state === sWaitAddr)

  // --------------------------------------------------------------------------
  // AXI write data channel
  // --------------------------------------------------------------------------
  io.w.ready := (state === sIdle) || (state === sWaitData)

  // --------------------------------------------------------------------------
  // AXI write response channel
  // --------------------------------------------------------------------------
  io.b.valid := (state === sResp)
  io.b.bits.id := awReg.id
  io.b.bits.resp := 0.U // OKAY
  io.b.bits.user := 0.U

  // --------------------------------------------------------------------------
  // AXI read channel (not implemented)
  // --------------------------------------------------------------------------
  io.ar.ready := false.B
  io.r.valid := false.B
  io.r.bits.id := 0.U
  io.r.bits.data := 0.U
  io.r.bits.resp := 0.U
  io.r.bits.last := false.B
  io.r.bits.user := 0.U

  // --------------------------------------------------------------------------
  // UART connection
  // --------------------------------------------------------------------------
  uart.io.en := (state === sWrite)
  uart.io.data := wReg.data(7, 0)
}
