package peripheral.mem

import chisel3._
import chisel3.util._
import riscv.util._
import riscv.util.DpiMem

// ============================================================
// Common Config
// ============================================================

case class MemDelayConfig(
  enable: Boolean = false,
  delayWidth: Int = 8,
  delaySeed: Int = 2,
  delayTaps: Int = 0x9
)

// ============================================================
// ROM Interface
// ============================================================

class InstReq(val dataWidth: Int) extends Bundle {
  val addr = UInt(dataWidth.W)
}
class InstResp(val dataWidth: Int) extends Bundle {
  val data = UInt(dataWidth.W)
}
class InstBus(val dataWidth: Int) extends Bundle {
  val req  = Decoupled(new InstReq(dataWidth))
  val resp = Flipped(Decoupled(new InstResp(dataWidth)))
}

// ============================================================
// RAM Interface
// ============================================================

class DataReq(val dataWidth: Int) extends Bundle {
  val ren   = Bool()
  val wen   = Bool()
  val mask  = UInt((dataWidth/8).W)
  val addr  = UInt(dataWidth.W)
  val wdata = UInt(dataWidth.W)
}
class DataResp(val dataWidth: Int) extends Bundle {
  val rdata = UInt(dataWidth.W)
}
class DataBus(val dataWidth: Int) extends Bundle {
  val req  = Decoupled(new DataReq(dataWidth))
  val resp = Flipped(Decoupled(new DataResp(dataWidth)))
}

// ============================================================
// Base ROM
// ============================================================

class BaseROM(
  useDpiMem: Boolean = true,
  dataDepth: Int,
  dataWidth: Int,
  initFile: Option[String] = None
) extends Module {
  require(dataDepth > 1)
  require(dataWidth % 8 == 0)
  val io = IO(Flipped(new InstBus(dataWidth)))
  private val addrWidth = log2Ceil(dataDepth)
    // request control
    val busy = RegInit(false.B)
    val fireReq = io.req.valid && !busy
    io.req.ready := !busy
    // address
    val addr = io.req.bits.addr(addrWidth - 1, 0)
    // memory backend
    val rdataWire = Wire(UInt(dataWidth.W))
    if (!useDpiMem) {
      // SyncReadMem backend
      val mem = SyncReadMem(dataDepth, UInt(dataWidth.W))
      import chisel3.util.experimental.loadMemoryFromFileInline
      initFile.foreach(loadMemoryFromFileInline(mem, _))
      rdataWire := mem.read(addr, fireReq)
    } else {
      // DpiMem backend
      val mem = Module(new DpiMem)
      mem.io.ren   <> true.B
      mem.io.wen   <> false.B
      mem.io.mask  <> 0xF.U
      mem.io.addr  <> io.req.bits.addr
      mem.io.wdata <> 0.U
      mem.io.rdata <> rdataWire
    }
    // read response
    val dataReg = RegEnable(rdataWire, fireReq)
    val respValidReg = RegNext(fireReq, false.B)
    io.resp.bits.data := dataReg
    io.resp.valid := respValidReg
    // busy control
    when(fireReq) {
      busy := true.B
    }
    when(io.resp.valid && io.resp.ready) {
      busy := false.B
    }
}

// ============================================================
// Base RAM
// ============================================================

class BaseRAM(
  useDpiMem: Boolean = true,
  dataDepth: Int,
  dataWidth: Int
) extends Module {
  require(dataDepth > 1)
  require(dataWidth % 8 == 0)
  val io = IO(Flipped(new DataBus(dataWidth)))
  private val addrWidth = log2Ceil(dataDepth)
  private val maskWidth = dataWidth / 8
    // request control
    val busy    = RegInit(false.B)
    val fireReq = io.req.valid && !busy
    io.req.ready := !busy
    val addr = io.req.bits.addr(addrWidth - 1, 0)
    // write data split
    val wdataVec = Wire(Vec(maskWidth, UInt(8.W)))
    for (i <- 0 until maskWidth) {
      wdataVec(i) := io.req.bits.wdata(8 * (i + 1) - 1, 8 * i)
    }
    // memory backend
    val rdataWire = Wire(UInt(dataWidth.W))
    if (!useDpiMem) {
      // SyncReadMem backend
      val mem = SyncReadMem(dataDepth, Vec(maskWidth, UInt(8.W)))
      when(fireReq && io.req.bits.wen) {
        mem.write(addr, wdataVec, io.req.bits.mask.asBools)
      }
      val rdataVec = mem.read(addr, fireReq && io.req.bits.ren)
      rdataWire := rdataVec.asUInt
    } else {
      // DPI memory backend
      val mem = Module(new DpiMem)
      mem.io.ren   <> io.req.bits.ren
      mem.io.wen   <> io.req.bits.wen
      mem.io.mask  <> io.req.bits.mask
      mem.io.addr  <> io.req.bits.addr
      mem.io.wdata <> io.req.bits.wdata
      mem.io.rdata <> rdataWire
    }
    // read response
    val rdataReg = RegEnable(rdataWire, fireReq && io.req.bits.ren)
    val respValidReg = RegInit(false.B)
    when(fireReq && io.req.bits.ren) {
      respValidReg := true.B
    }.elsewhen(io.resp.valid && io.resp.ready) {
      respValidReg := false.B
    }
    io.resp.bits.rdata := rdataReg
    io.resp.valid := respValidReg
    // busy control
    when(fireReq && io.req.bits.ren) {
      busy := true.B
    }
    when(io.resp.valid && io.resp.ready) {
      busy := false.B
    }
    when(fireReq && io.req.bits.wen && !io.req.bits.ren) {
      busy := false.B
    }
}

// ============================================================
// Random Delay Helper
// ============================================================

trait RandomDelaySupport { this: Module =>
  protected def buildDelay(
    validIn   : Bool,
    readyIn   : Bool,
    dataIn    : UInt,
    dataWidth : Int,
    cfg       : MemDelayConfig
  ): (UInt, Bool) = {
    val lfsr = Module(new LFSR(cfg.delayWidth, cfg.delaySeed, cfg.delayTaps))
    lfsr.io.en := true.B
    val waitingResp = RegInit(false.B)
    val delayCnt    = RegInit(0.U(cfg.delayWidth.W))
    val dataReg  = Reg(UInt(dataWidth.W))
    val validReg = RegInit(false.B)
    when(validIn && readyIn) {
      dataReg     := dataIn
      delayCnt    := lfsr.io.data
      waitingResp := true.B
    }
    when(validReg) {
      validReg := false.B
    }
    when(waitingResp) {
      when(delayCnt =/= 0.U) {
        delayCnt := delayCnt - 1.U
      }.otherwise {
        validReg    := true.B
        waitingResp := false.B
      }
    }
    (dataReg, validReg)
  }
}

// ============================================================
// ROM Top
// ============================================================

class ROM(
  useDpiMem: Boolean = true,
  dataDepth: Int = 512,
  dataWidth: Int = 32,
  initFile: Option[String] = None,
  delayCfg: MemDelayConfig = MemDelayConfig()
) extends Module with RandomDelaySupport {
  val io = IO(Flipped(new InstBus(dataWidth)))
  private val rom = Module(new BaseROM(useDpiMem, dataDepth, dataWidth, initFile))
  rom.io.req.bits.addr <> io.req.bits.addr
  rom.io.req.valid  <> io.req.valid
  rom.io.req.ready  <> io.req.ready
  rom.io.resp.ready <> io.resp.ready
  if (delayCfg.enable) {
    val (data, valid) = buildDelay(
      validIn   = rom.io.resp.valid,
      readyIn   = rom.io.resp.ready,
      dataIn    = rom.io.resp.bits.data,
      dataWidth = dataWidth,
      cfg       = delayCfg
    )
    io.resp.bits.data := data
    io.resp.valid := valid
  } else {
    io.resp.bits.data := rom.io.resp.bits.data
    io.resp.valid := rom.io.resp.valid
  }
}

// ============================================================
// RAM Top
// ============================================================

class RAM(
  useDpiMem: Boolean = true,
  dataDepth: Int = 512,
  dataWidth: Int = 32,
  delayCfg: MemDelayConfig = MemDelayConfig()
) extends Module with RandomDelaySupport {
  val io = IO(Flipped(new DataBus(dataWidth)))
  private val ram = Module(new BaseRAM(useDpiMem, dataDepth, dataWidth))
  ram.io.req.valid  <> io.req.valid
  ram.io.req.bits.addr  <> io.req.bits.addr
  ram.io.req.bits.wdata <> io.req.bits.wdata
  ram.io.req.bits.mask  <> io.req.bits.mask
  ram.io.req.bits.ren   <> io.req.bits.ren
  ram.io.req.bits.wen   <> io.req.bits.wen
  ram.io.req.ready  <> io.req.ready
  ram.io.resp.ready <> io.resp.ready
  if (delayCfg.enable) {
    val (data, valid) = buildDelay(
      validIn   = ram.io.resp.valid,
      readyIn   = ram.io.resp.ready,
      dataIn    = ram.io.resp.bits.rdata,
      dataWidth = dataWidth,
      cfg       = delayCfg
    )
    io.resp.bits.rdata := data
    io.resp.valid := valid
  } else {
    io.resp.bits.rdata := ram.io.resp.bits.rdata
    io.resp.valid := ram.io.resp.valid
  }
}
