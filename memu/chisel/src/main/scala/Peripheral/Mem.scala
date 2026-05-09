package peripheral.mem

import chisel3._
import chisel3.util._
import riscv.util.{DpiMem, LFSR}

// ============================================================
// Config
// ============================================================

case class MemDelayConfig(
  enable    : Boolean = false,
  delayWidth: Int     = 8,
  delaySeed : Int     = 2,
  delayTaps : Int     = 0x9
)

// ============================================================
// Bus Definitions
// ============================================================

class InstReq(w: Int) extends Bundle {
  val addr = UInt(w.W)
}
class InstResp(w: Int) extends Bundle {
  val data = UInt(w.W)
}
class InstBus(w: Int) extends Bundle {
  val req  = Decoupled(new InstReq(w))
  val resp = Flipped(Decoupled(new InstResp(w)))
}

class DataReq(w: Int) extends Bundle {
  val ren   = Bool()
  val wen   = Bool()
  val mask  = UInt((w/8).W)
  val addr  = UInt(w.W)
  val wdata = UInt(w.W)
}
class DataResp(w: Int) extends Bundle {
  val rdata = UInt(w.W)
}
class DataBus(w: Int) extends Bundle {
  val req  = Decoupled(new DataReq(w))
  val resp = Flipped(Decoupled(new DataResp(w)))
}

// ============================================================
// Random Delay
// ============================================================

trait RandomDelay { this: Module =>
  protected def applyDelay(
    fire : Bool,
    data : UInt,
    width: Int,
    cfg  : MemDelayConfig
  ): (UInt, Bool) = {
    val lfsr = Module(new LFSR(cfg.delayWidth, cfg.delaySeed, cfg.delayTaps))
    lfsr.io.en := true.B
    val waiting = RegInit(false.B)
    val counter = Reg(UInt(cfg.delayWidth.W))
    val dataReg = Reg(UInt(width.W))
    val valid   = RegInit(false.B)
    valid := false.B
    when(fire) {
      dataReg := data
      counter := lfsr.io.data
      waiting := true.B
    }
    when(waiting) {
      when(counter.orR) {
        counter := counter - 1.U
      }.otherwise {
        valid   := true.B
        waiting := false.B
      }
    }
    (dataReg, valid)
  }
}

// ============================================================
// Memory Backend
// ============================================================

class BaseROM(
  useDpi   : Boolean = true,
  depth    : Int,
  width    : Int,
  initFile : Option[String] = None
) extends Module {
  require(depth > 1)
  require(width % 8 == 0)
  val io = IO(Flipped(new InstBus(width)))
  private val addrWidth = log2Ceil(depth)
  // request control
  val fire = io.req.fire
  val busy = RegInit(false.B)
  io.req.ready := !busy
  // address
  val addr  = io.req.bits.addr(addrWidth - 1, 0)
  // memory backend
  val rdata = Wire(UInt(width.W))
  if (useDpi) {
    // DpiMem backend
    val mem = Module(new DpiMem)
    mem.io.ren   := true.B
    mem.io.wen   := false.B
    mem.io.mask  := Fill(width / 8, 1.U(1.W))
    mem.io.addr  := io.req.bits.addr
    mem.io.wdata := 0.U
    rdata := mem.io.rdata
  } else {
    // SyncReadMem backend
    import chisel3.util.experimental.loadMemoryFromFileInline
    val mem = SyncReadMem(depth, UInt(width.W))
    initFile.foreach(loadMemoryFromFileInline(mem, _))
    rdata := mem.read(addr, fire)
  }
  // read response
  io.resp.bits.data := RegEnable(rdata, fire)
  io.resp.valid     := RegNext(fire, false.B)
  // busy control
  when(fire) {
    busy := true.B
  }
  when(io.resp.fire) {
    busy := false.B
  }
}

class BaseRAM(
  useDpi : Boolean = true,
  depth  : Int,
  width  : Int
) extends Module {
  require(depth > 1)
  require(width % 8 == 0)
  val io = IO(Flipped(new DataBus(width)))
  private val addrWidth = log2Ceil(depth)
  private val maskWidth = width / 8
  // request control
  val busy = RegInit(false.B)
  io.req.ready := !busy
  val fire = io.req.fire
  val ren  = io.req.bits.ren
  val wen  = io.req.bits.wen
  val addr = io.req.bits.addr(addrWidth - 1, 0)
  // memory backend
  val rdata = Wire(UInt(width.W))
  if (useDpi) {
    // DPI memory backend
    val mem = Module(new DpiMem)
    mem.io.ren   := ren
    mem.io.wen   := wen
    mem.io.mask  := io.req.bits.mask
    mem.io.addr  := io.req.bits.addr
    mem.io.wdata := io.req.bits.wdata
    rdata := mem.io.rdata
  } else {
    // SyncReadMem backend
    val mem = SyncReadMem(depth, Vec(maskWidth, UInt(8.W)))
    val wdata = io.req.bits.wdata.asTypeOf(Vec(maskWidth, UInt(8.W)))
    when(fire && wen) {
      mem.write(addr, wdata, io.req.bits.mask.asBools)
    }
    rdata := mem.read(addr, fire && ren).asUInt
  }
  // read response
  io.resp.bits.rdata := RegEnable(rdata, fire && ren)
  val respValid = RegInit(false.B)
  when(fire && ren) {
    respValid := true.B
  }.elsewhen(io.resp.fire) {
    respValid := false.B
  }
  // busy control
  io.resp.valid := respValid
  when(fire && ren) {
    busy := true.B
  }
  when(io.resp.fire || (fire && wen && !ren)) {
    busy := false.B
  }
}

// ============================================================
// Memory
// ============================================================

class ROM(
  useDpi: Boolean = true,
  depth    : Int  = 512,
  width    : Int  = 32,
  initFile : Option[String] = None,
  delayCfg : MemDelayConfig = MemDelayConfig()
) extends Module with RandomDelay {
  val io = IO(Flipped(new InstBus(width)))
  private val rom = Module(new BaseROM(useDpi, depth, width, initFile))
  rom.io.req <> io.req
  rom.io.resp.ready := io.resp.ready
  if (delayCfg.enable) {
    val (data, valid) = applyDelay(
      fire  = rom.io.resp.fire,
      data  = rom.io.resp.bits.data,
      width = width,
      cfg   = delayCfg
    )
    io.resp.bits.data := data
    io.resp.valid     := valid
  } else {
    io.resp <> rom.io.resp
  }
}

class RAM(
  useDpi: Boolean = true,
  depth    : Int  = 512,
  width    : Int  = 32,
  delayCfg : MemDelayConfig = MemDelayConfig()
) extends Module with RandomDelay {
  val io = IO(Flipped(new DataBus(width)))
  private val ram = Module(new BaseRAM(useDpi, depth, width))
  ram.io.req <> io.req
  ram.io.resp.ready := io.resp.ready
  if (delayCfg.enable) {
    val (data, valid) = applyDelay(
      fire  = ram.io.resp.fire,
      data  = ram.io.resp.bits.rdata,
      width = width,
      cfg   = delayCfg
    )
    io.resp.bits.rdata := data
    io.resp.valid      := valid
  } else {
    io.resp <> ram.io.resp
  }
}

// ============================================================
// AXI Memory
// ============================================================
import bus.amba.axi.common._

class Axi4Rom(p: AxiParams, depthWords: Int = 1024, initFile: String = "") extends Module {
  require(depthWords > 1, "depthWords must be greater than 1")
  require((p.dataBits % 8) == 0, "AXI dataBits must be byte aligned")
  val io = IO(new Bundle {
    val axi = new AXI4SlaveBundle(p)
  })

  def this(depthWords: Int, initFile: String)(implicit params: AxiParameters) =
    this(AxiParams.fromPortParameters, depthWords, initFile)

  private val dataBytes = p.dataBits / 8
  private val wordShift = log2Ceil(dataBytes)
  private val depthBits = log2Ceil(depthWords)
  private val sizeMatch = log2Ceil(dataBytes).U(3.W)

  import chisel3.util.experimental.loadMemoryFromFileInline
  private val mem = Mem(depthWords, UInt(p.dataBits.W))
  if (initFile.nonEmpty) {
    loadMemoryFromFileInline(mem, initFile)
  }
  private def inRange(addr: UInt): Bool = {
    val idx = (addr >> wordShift)(depthBits - 1, 0)
    idx < depthWords.U
  }

  // -------------------------
  // Write path: always SLVERR
  // -------------------------
  val wIdle :: wData :: wResp :: Nil = Enum(3)
  val wState = RegInit(wIdle)
  val wId    = Reg(UInt(p.idBits.W))
  val awSeen = RegInit(false.B)
  val wSeen  = RegInit(false.B)

  io.axi.aw.ready := (wState === wIdle) && !awSeen
  io.axi.w.ready  := (wState === wIdle || wState === wData) && !wSeen

  io.axi.b.valid     := (wState === wResp)
  io.axi.b.bits.id   := wId
  io.axi.b.bits.resp := AxiResp.SLVERR
  io.axi.b.bits.user := 0.U

  when((wState === wIdle || wState === wData) && io.axi.aw.fire) {
    wId    := io.axi.aw.bits.id
    awSeen := true.B
    when(wSeen) { wState := wResp }
      .otherwise { wState := wData }
  }
  when((wState === wIdle || wState === wData) && io.axi.w.fire) {
    wSeen := true.B
    when(awSeen && io.axi.w.bits.last) {
      wState := wResp
    }.otherwise {
      wState := wData
    }
  }
  when(wState === wResp && io.axi.b.fire) {
    awSeen := false.B
    wSeen  := false.B
    wState := wIdle
  }

  // -------------------------
  // Read path (AR/R)
  // -------------------------
  val rIdle :: rData :: Nil = Enum(2)
  val rState = RegInit(rIdle)
  val rId    = Reg(UInt(p.idBits.W))
  val rAddr  = Reg(UInt(p.addrBits.W))
  val rBurst = Reg(UInt(2.W))
  val rSize  = Reg(UInt(3.W))
  val rBeats = Reg(UInt(9.W))

  io.axi.ar.ready := (rState === rIdle)

  io.axi.r.valid     := (rState === rData)
  io.axi.r.bits.id   := rId
  io.axi.r.bits.data := 0.U
  io.axi.r.bits.resp := AxiResp.OKAY
  io.axi.r.bits.last := (rBeats === 1.U)
  io.axi.r.bits.user := 0.U
  when(rState === rIdle && io.axi.ar.fire) {
    rId    := io.axi.ar.bits.id
    rAddr  := io.axi.ar.bits.addr
    rBurst := io.axi.ar.bits.burst
    rSize  := io.axi.ar.bits.size
    rBeats := io.axi.ar.bits.len + 1.U
    rState := rData
  }
  when(rState === rData) {
    val addrOk  = inRange(rAddr)
    val sizeOk  = (rSize === sizeMatch)
    val burstOk = (rBurst === AxiBurst.INCR) || (rBurst === AxiBurst.FIXED)
    when(addrOk && sizeOk && burstOk) {
      val idx = (rAddr >> wordShift)(depthBits - 1, 0)
      io.axi.r.bits.data := mem.read(idx)
      io.axi.r.bits.resp := AxiResp.OKAY
    }.otherwise {
      io.axi.r.bits.data := 0.U
      io.axi.r.bits.resp := AxiResp.SLVERR
    }
    when(io.axi.r.fire) {
      when(rBeats === 1.U) {
        rState := rIdle
      }.otherwise {
        rBeats := rBeats - 1.U
        when(rBurst === AxiBurst.INCR) {
          rAddr := rAddr + dataBytes.U
        }
      }
    }
  }
}

class Axi4Ram(p: AxiParams, depthWords: Int = 1024) extends Module {
  require(depthWords > 1, "depthWords must be greater than 1")
  require((p.dataBits % 8) == 0, "AXI dataBits must be byte aligned")
  val io = IO(new Bundle {
    val axi = new AXI4SlaveBundle(p)
  })

  def this(depthWords: Int)(implicit params: AxiParameters) =
    this(AxiParams.fromPortParameters, depthWords)

  private val dataBytes = p.dataBits / 8
  private val wordShift = log2Ceil(dataBytes)
  private val depthBits = log2Ceil(depthWords)
  private val sizeMatch = log2Ceil(dataBytes).U(3.W)

  private val mem = Mem(depthWords, UInt(p.dataBits.W))
  private def inRange(addr: UInt): Bool = {
    val idx = (addr >> wordShift)(depthBits - 1, 0)
    idx < depthWords.U
  }
  private def mergeBytes(oldData: UInt, newData: UInt, strb: UInt): UInt = {
    val lanes = (0 until p.strobeBits).map { i =>
      val lo = i * 8
      Mux(strb(i), newData(lo + 7, lo), oldData(lo + 7, lo))
    }
    Cat(lanes.reverse)
  }

  // -------------------------
  // Write path (AW/W/B)
  // -------------------------
  val wIdle :: wData :: wResp :: Nil = Enum(3)
  val wState = RegInit(wIdle)

  val wId      = Reg(UInt(p.idBits.W))
  val wAddr    = Reg(UInt(p.addrBits.W))
  val wBurst   = Reg(UInt(2.W))
  val wSize    = Reg(UInt(3.W))
  val wBeats   = Reg(UInt(9.W)) // len + 1, up to 256
  val wRespReg = RegInit(AxiResp.OKAY)

  io.axi.aw.ready := (wState === wIdle)
  io.axi.w.ready  := (wState === wData)

  io.axi.b.valid     := (wState === wResp)
  io.axi.b.bits.id   := wId
  io.axi.b.bits.resp := wRespReg
  io.axi.b.bits.user := 0.U

  when(wState === wIdle && io.axi.aw.fire) {
    wId      := io.axi.aw.bits.id
    wAddr    := io.axi.aw.bits.addr
    wBurst   := io.axi.aw.bits.burst
    wSize    := io.axi.aw.bits.size
    wBeats   := io.axi.aw.bits.len + 1.U
    wRespReg := AxiResp.OKAY
    wState   := wData
  }
  when(wState === wData && io.axi.w.fire) {
    val addrOk  = inRange(wAddr)
    val sizeOk  = (wSize === sizeMatch)
    val burstOk = (wBurst === AxiBurst.INCR) || (wBurst === AxiBurst.FIXED)
    when(addrOk && sizeOk && burstOk) {
      val idx     = (wAddr >> wordShift)(depthBits - 1, 0)
      val oldData = mem.read(idx)
      mem.write(idx, mergeBytes(oldData, io.axi.w.bits.data, io.axi.w.bits.strb))
    }.otherwise {
      wRespReg := AxiResp.SLVERR
    }
    val lastBeatByCount = (wBeats === 1.U)
    val txnDone         = io.axi.w.bits.last || lastBeatByCount
    when(txnDone) {
      wState := wResp
    }.otherwise {
      wBeats := wBeats - 1.U
      when(wBurst === AxiBurst.INCR) {
        wAddr := wAddr + dataBytes.U
      }
    }
  }
  when(wState === wResp && io.axi.b.fire) {
    wState := wIdle
  }

  // -------------------------
  // Read path (AR/R)
  // -------------------------
  val rIdle :: rData :: Nil = Enum(2)
  val rState = RegInit(rIdle)
  val rId    = Reg(UInt(p.idBits.W))
  val rAddr  = Reg(UInt(p.addrBits.W))
  val rBurst = Reg(UInt(2.W))
  val rSize  = Reg(UInt(3.W))
  val rBeats = Reg(UInt(9.W))

  io.axi.ar.ready := (rState === rIdle)

  io.axi.r.valid     := (rState === rData)
  io.axi.r.bits.id   := rId
  io.axi.r.bits.data := 0.U
  io.axi.r.bits.resp := AxiResp.OKAY
  io.axi.r.bits.last := (rBeats === 1.U)
  io.axi.r.bits.user := 0.U

  when(rState === rIdle && io.axi.ar.fire) {
    rId    := io.axi.ar.bits.id
    rAddr  := io.axi.ar.bits.addr
    rBurst := io.axi.ar.bits.burst
    rSize  := io.axi.ar.bits.size
    rBeats := io.axi.ar.bits.len + 1.U
    rState := rData
  }
  when(rState === rData) {
    val addrOk  = inRange(rAddr)
    val sizeOk  = (rSize === sizeMatch)
    val burstOk = (rBurst === AxiBurst.INCR) || (rBurst === AxiBurst.FIXED)
    when(addrOk && sizeOk && burstOk) {
      val idx = (rAddr >> wordShift)(depthBits - 1, 0)
      io.axi.r.bits.data := mem.read(idx)
      io.axi.r.bits.resp := AxiResp.OKAY
    }.otherwise {
      io.axi.r.bits.data := 0.U
      io.axi.r.bits.resp := AxiResp.SLVERR
    }
    when(io.axi.r.fire) {
      when(rBeats === 1.U) {
        rState := rIdle
      }.otherwise {
        rBeats := rBeats - 1.U
        when(rBurst === AxiBurst.INCR) {
          rAddr := rAddr + dataBytes.U
        }
      }
    }
  }
}
