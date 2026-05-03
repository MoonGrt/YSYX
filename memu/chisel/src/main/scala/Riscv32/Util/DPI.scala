package riscv.util

import chisel3._
import chisel3.util._
import riscv.Instructions._
import riscv.Constants._
import riscv.util.LFSR

// ---------------------------
// ROM BlackBox (只读指令存储器)
// ---------------------------
class ROM_DPI extends BlackBox{
  val io = IO(new Bundle {
    val clock      = Input(Clock())
    val reset      = Input(Bool())
    // req
    val req_ready  = Output(Bool())
    val addr       = Input(UInt(DataWidth.W))
    val req_valid  = Input(Bool())
    // resp
    val resp_ready = Input(Bool())
    val data       = Output(UInt(DataWidth.W))
    val resp_valid = Output(Bool())
  })
}
class RandomDelayROM(delayWidth: Int = 8, seed: Int = 2, taps: Int = 0x9) extends Module {
  val io = IO(new Bundle {
    val clock      = Input(Clock())
    val reset      = Input(Bool())
    // req
    val req_ready  = Output(Bool())
    val addr       = Input(UInt(DataWidth.W))
    val req_valid  = Input(Bool())
    // resp
    val resp_ready = Input(Bool())
    val data       = Output(UInt(DataWidth.W))
    val resp_valid = Output(Bool())
  })

  val rom = Module(new ROM_DPI)
  rom.io.clock <> io.clock
  rom.io.reset <> io.reset

  val lfsr = Module(new LFSR(delayWidth, seed, taps))
  lfsr.io.en := true.B
  // lfsr.io.en := false.B

  val waitingResp = RegInit(false.B)
  val delayCnt    = RegInit(0.U(delayWidth.W))
  val dataReg     = Reg(UInt(DataWidth.W))
  val validReg    = RegInit(false.B)

  rom.io.req_valid := io.req_valid
  rom.io.addr      := io.addr
  rom.io.resp_ready := io.resp_ready

  io.req_ready := rom.io.req_ready
  io.data := dataReg
  io.resp_valid := validReg

  when(rom.io.resp_valid && rom.io.resp_ready) {
    dataReg := rom.io.data
    delayCnt := lfsr.io.data
    waitingResp := true.B
  }

  when(validReg) {
    validReg := false.B
  }

  when(waitingResp) {
    when(delayCnt =/= 0.U) {
      delayCnt := delayCnt - 1.U
    }.otherwise {
      validReg := true.B
      waitingResp := false.B
    }
  }
}

// ---------------------------
// RAM BlackBox (可读写数据存储器)
// ---------------------------
class RAM_DPI extends BlackBox {
  val io = IO(new Bundle {
    val clock      = Input(Clock())
    val reset      = Input(Bool())
    // req
    val req_ready  = Output(Bool())
    val ren        = Input(Bool())
    val wen        = Input(Bool())
    val mask       = Input(UInt(8.W))
    val addr       = Input(UInt(DataWidth.W))
    val wdata      = Input(UInt(DataWidth.W))
    val req_valid  = Input(Bool())
    // resp
    val resp_ready = Input(Bool())
    val rdata      = Output(UInt(DataWidth.W))
    val resp_valid = Output(Bool())
  })
}
class RandomDelayRAM(delayWidth: Int = 8, seed: Int = 2, taps: Int = 0x9) extends Module {
  val io = IO(new Bundle {
    val clock      = Input(Clock())
    val reset      = Input(Bool())
    // req
    val req_ready  = Output(Bool())
    val ren        = Input(Bool())
    val wen        = Input(Bool())
    val mask       = Input(UInt(8.W))
    val addr       = Input(UInt(DataWidth.W))
    val wdata      = Input(UInt(DataWidth.W))
    val req_valid  = Input(Bool())
    // resp
    val resp_ready = Input(Bool())
    val rdata      = Output(UInt(DataWidth.W))
    val resp_valid = Output(Bool())
  })

  val ram = Module(new RAM_DPI)
  ram.io.clock <> io.clock
  ram.io.reset <> io.reset

  val lfsr = Module(new LFSR(delayWidth, seed, taps))
  lfsr.io.en := true.B
  // lfsr.io.en := false.B

  val waitingResp = RegInit(false.B)
  val delayCnt    = RegInit(0.U(delayWidth.W))
  val dataReg     = Reg(UInt(DataWidth.W))
  val validReg    = RegInit(false.B)

  ram.io.req_valid := io.req_valid
  ram.io.addr  := io.addr
  ram.io.wdata := io.wdata
  ram.io.mask  := io.mask
  ram.io.ren   := io.ren
  ram.io.wen   := io.wen
  ram.io.resp_ready := io.resp_ready

  io.req_ready := ram.io.req_ready
  io.rdata := dataReg
  io.resp_valid := validReg

  when(ram.io.resp_valid && ram.io.resp_ready) {
    dataReg := ram.io.rdata
    delayCnt := lfsr.io.data
    waitingResp := true.B
  }

  when(validReg) {
    validReg := false.B
  }

  when(waitingResp) {
    when(delayCnt =/= 0.U) {
      delayCnt := delayCnt - 1.U
    }.otherwise {
      validReg := true.B
      waitingResp := false.B
    }
  }
}

// ---------------------------
// Exception BlackBox (异常处理模块)
// ---------------------------
class Exception extends BlackBox {
  val io = IO(new Bundle {
    val clk  = Input(Clock())
    val en   = Input(Bool())
    val code = Input(UInt(8.W))
  })
}

class Trap(val impled: Seq[BitPat]) extends Module {
  val io = IO(new Bundle {
    val valid = Input(Bool())
    val inst  = Input(UInt(DataWidth.W))
    val halt  = Output(Bool())
  })
  // -------- 异常类型 --------
  val is_ebreak = io.valid && (io.inst === EBREAK)
  val is_ecall  = io.valid && (io.inst === ECALL)
  val is_zero   = io.valid && (io.inst === 0.U)
  val is_impl   = io.valid && VecInit(impled.map(_ === io.inst)).asUInt.orR
  val is_unimpl = io.valid && ~is_impl
  val ecode = MuxCase(0.U, Seq(
    is_ebreak -> 0.U,
    is_ecall  -> 1.U,
    is_zero   -> 2.U,
    is_unimpl -> 3.U,
  ))
  // -------- Exception --------
  val exception = Module(new Exception)
  exception.io.clk  := clock
  exception.io.en   := io.valid && ~reset.asBool && 
                       (is_unimpl || is_zero || is_ebreak || is_ecall)
  exception.io.code := ecode
  // -------- halt --------
  io.halt := io.valid && ~reset.asBool && is_unimpl
}

// ---------------------------
// DiffTest BlackBox (差分测试模块)
// ---------------------------
class DiffPC extends BlackBox {
  val io = IO(new Bundle {
    val clk  = Input(Clock())
    val en   = Input(Bool())
    val pc   = Input(UInt(DataWidth.W))
    val npc  = Input(UInt(DataWidth.W))
    val inst = Input(UInt(DataWidth.W))
  })
}
class DiffGPR extends BlackBox {
  val io = IO(new Bundle {
    val gpr  = Input(Vec(GPRNum, UInt(DataWidth.W)))
  })
}
class DiffCSR extends BlackBox {
  val io = IO(new Bundle {
    val csr  = Input(Vec(CSRNum, UInt(DataWidth.W)))
  })
}
