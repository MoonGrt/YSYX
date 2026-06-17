package soc.perip.mem

import chisel3._
import chisel3.util._
import soc.util.{DpiMem, LFSR}

// ============================================================
// Config
// ============================================================

object BusType extends ChiselEnum {
  val SimpleBus, AXI = Value
}

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

class AXIROM(
  p: AxiParams,
  useDpi: Boolean = true,
  depth: Int = 1024,
  width: Int = 32,
  initFile: Option[String] = None
) extends Module {
  require(depth > 1)
  require(width % 8 == 0)
  val io = IO(new AXI4SlaveBundle(p))
  private val addrWidth = log2Ceil(depth)

  val arFire = io.ar.fire
  val rFire  = io.r.fire

  val busy = RegInit(false.B)

  io.ar.ready := !busy

  val addr = io.ar.bits.addr(addrWidth - 1, 0)
  val rdata = Wire(UInt(width.W))

  if (useDpi) {
    val mem = Module(new DpiMem)
    mem.io.ren := true.B
    mem.io.wen := false.B
    mem.io.mask := Fill(width / 8, 1.U(1.W))
    mem.io.addr := io.ar.bits.addr
    mem.io.wdata := 0.U
    rdata := mem.io.rdata
  } else {
    import chisel3.util.experimental.loadMemoryFromFileInline
    val mem = SyncReadMem(depth, UInt(width.W))
    initFile.foreach(loadMemoryFromFileInline(mem, _))
    rdata := mem.read(addr, arFire)
  }

  io.r.bits.data := RegEnable(rdata, arFire)
  io.r.bits.id   := RegNext(io.ar.bits.id)
  io.r.bits.resp := 0.U
  io.r.bits.last := true.B
  io.r.bits.user := 0.U

  io.r.valid := RegNext(arFire, false.B)

  when(arFire) { busy := true.B }
  when(rFire)  { busy := false.B }

  io.aw.ready := false.B
  io.w.ready := false.B
  io.b.valid := false.B
  io.b.bits.id   := 0.U
  io.b.bits.resp := 0.U
  io.b.bits.user := 0.U
}

class AXIRAM(
  p: AxiParams,
  useDpi: Boolean = true,
  depth: Int = 1024,
  width: Int = 32,
  delayCfg: MemDelayConfig = MemDelayConfig()
) extends Module with RandomDelay {
  require(depth > 1)
  require(width % 8 == 0)
  val io = IO(new AXI4SlaveBundle(p))

  // ----------------------------------------------------------------
  // Base RAM
  // ----------------------------------------------------------------
  val ram = Module(new BaseRAM(useDpi, depth, width))
  ram.io.req.valid := false.B
  ram.io.req.bits  := DontCare
  ram.io.resp.ready := true.B

  // ----------------------------------------------------------------
  // Write channel state
  // ----------------------------------------------------------------
  val awValidReg = RegInit(false.B)
  val wValidReg  = RegInit(false.B)
  val awAddrReg = Reg(UInt(p.addrBits.W))
  val awIdReg   = Reg(UInt(p.idBits.W))
  val wDataReg = Reg(UInt(p.dataBits.W))
  val wStrbReg = Reg(UInt((p.dataBits / 8).W))
  val bValidReg = RegInit(false.B)
  val bIdReg    = Reg(UInt(p.idBits.W))

  // ----------------------------------------------------------------
  // Read channel state
  // ----------------------------------------------------------------
  val rValidReg = RegInit(false.B)
  val rDataReg  = Reg(UInt(width.W))
  val rIdReg    = Reg(UInt(p.idBits.W))

  // ----------------------------------------------------------------
  // Busy
  // single outstanding transaction
  // ----------------------------------------------------------------
  val busy = RegInit(false.B)

  // ----------------------------------------------------------------
  // Default outputs
  // ----------------------------------------------------------------
  io.aw.ready := !busy && !awValidReg
  io.w.ready  := !busy && !wValidReg
  io.ar.ready := !busy

  io.b.valid := bValidReg
  io.b.bits.id := bIdReg
  io.b.bits.resp := 0.U
  io.b.bits.user := 0.U

  io.r.valid := rValidReg
  io.r.bits.data := rDataReg
  io.r.bits.id := rIdReg
  io.r.bits.resp := 0.U
  io.r.bits.last := true.B
  io.r.bits.user := 0.U

  // ----------------------------------------------------------------
  // Capture AW
  // ----------------------------------------------------------------
  when(io.aw.fire) {
    awValidReg := true.B
    awAddrReg  := io.aw.bits.addr
    awIdReg    := io.aw.bits.id
  }

  // ----------------------------------------------------------------
  // Capture W
  // ----------------------------------------------------------------
  when(io.w.fire) {
    wValidReg := true.B
    wDataReg  := io.w.bits.data
    wStrbReg  := io.w.bits.strb
  }

  // ----------------------------------------------------------------
  // Write issue
  // ----------------------------------------------------------------
  val writeFire = awValidReg && wValidReg && !bValidReg
  when(writeFire) {
    ram.io.req.valid := true.B
    ram.io.req.bits.wen := true.B
    ram.io.req.bits.ren := false.B
    ram.io.req.bits.addr := awAddrReg
    ram.io.req.bits.wdata := wDataReg
    ram.io.req.bits.mask := wStrbReg

    bValidReg := true.B
    bIdReg := awIdReg
    awValidReg := false.B
    wValidReg := false.B
    busy := true.B
  }

  // ----------------------------------------------------------------
  // Read request
  // ----------------------------------------------------------------
  val arFire = io.ar.fire
  when(arFire) {
    ram.io.req.valid := true.B
    ram.io.req.bits.ren := true.B
    ram.io.req.bits.wen := false.B
    ram.io.req.bits.addr := io.ar.bits.addr
    rIdReg := io.ar.bits.id
    busy := true.B
  }

  // ----------------------------------------------------------------
  // Read response
  // ----------------------------------------------------------------
  if(delayCfg.enable) {
    val (data, valid) = applyDelay(
      fire  = ram.io.resp.fire,
      data  = ram.io.resp.bits.rdata,
      width = width,
      cfg   = delayCfg
    )
    when(valid) {
      rDataReg := data
      rValidReg := true.B
    }
  } else {
    when(ram.io.resp.fire) {
      rDataReg := ram.io.resp.bits.rdata
      rValidReg := true.B
    }
  }
  when(io.r.fire) {
    rValidReg := false.B
    busy := false.B
  }

  // ----------------------------------------------------------------
  // Write response
  // ----------------------------------------------------------------
  when(io.b.fire) {
    bValidReg := false.B
    busy := false.B
  }
}

/** Minimal usage example: issue one read to ROM base address. */
class AXIROMExample extends Module {
  private implicit val params: AxiParameters = new BaseAxiConfig
  private val p = AxiParams.fromPortParameters
  val io = IO(new Bundle {
    val done = Output(Bool())
    val data = Output(UInt(p.dataBits.W))
    val resp = Output(UInt(2.W))
  })

  val host = Module(new bus.amba.axi.host.Axi4SingleBeatMasterHost(p))
  val rom  = Module(new AXIROM(p))
  rom.io <> host.io.axi

  val sReq :: sWait :: sDone :: Nil = Enum(3)
  val st = RegInit(sReq)
  val dataReg = RegInit(0.U(p.dataBits.W))
  val respReg = RegInit(AxiResp.OKAY)

  host.io.cmd.valid := false.B
  host.io.cmd.bits  := 0.U.asTypeOf(host.io.cmd.bits)
  host.io.rsp.ready := false.B
  switch(st) {
    is(sReq) {
      host.io.cmd.valid      := true.B
      host.io.cmd.bits.write := false.B
      host.io.cmd.bits.addr  := 0.U
      host.io.cmd.bits.wdata := 0.U
      host.io.cmd.bits.strb  := 0.U
      host.io.cmd.bits.prot  := 0.U
      when(host.io.cmd.fire) { st := sWait }
    }
    is(sWait) {
      host.io.rsp.ready := true.B
      when(host.io.rsp.fire) {
        dataReg := host.io.rsp.bits.rdata
        respReg := host.io.rsp.bits.resp
        st := sDone
      }
    }
  }
  io.done := (st === sDone)
  io.data := dataReg
  io.resp := respReg
}

// mill -i chisel.runMain soc.perip.mem.AXIROMExample --target-dir build/rtl
object AXIROMExample extends App {
  val firtoolOptions = Array(
    "--lowering-options=" + List(
      "disallowLocalVariables",
      "disallowPackedArrays",
      "locationInfoStyle=wrapInAtSquareBracket"
    ).reduce(_ + "," + _)
  )
  _root_.circt.stage.ChiselStage.emitSystemVerilogFile(new AXIROMExample, args, firtoolOptions)
}


/** Minimal usage example: write one word then read back. */
class AXIRAMExample extends Module {
  private val masterPort = AXI4MasterPortParameters(
    masters = Seq(AXI4MasterParameters(name = "axi4ram-example-master", id = IdRange(0, 4)))
  )
  private val slavePort = AXI4SlavePortParameters(
    slaves = Seq(
      AXI4SlaveParameters(
        address = Seq(AddressSet(base = 0, mask = 0xffff)),
        supportsWrite = TransferSizes(1, 4),
        supportsRead = TransferSizes(1, 4)
      )
    ),
    beatBytes = 4
  )

  private implicit val params: AxiParameters =
    new WithAxiPorts(masterPort, slavePort) ++ new BaseAxiConfig
  private val p: AxiParams = AxiParams.fromPortParameters
  private val ramDepthWords: Int =
    ((slavePort.maxAddress + 1) / slavePort.beatBytes).toInt

  val io = IO(new Bundle {
    val done     = Output(Bool())
    val readData = Output(UInt(p.dataBits.W))
    val readResp = Output(UInt(2.W))
  })

  val host = Module(new bus.amba.axi.host.Axi4SingleBeatMasterHost(p))
  val ram  = Module(new AXIRAM(p))
  ram.io <> host.io.axi

  val sWriteCmd :: sWaitWriteRsp :: sReadCmd :: sWaitReadRsp :: sDone :: Nil = Enum(5)
  val state = RegInit(sWriteCmd)

  host.io.cmd.valid := false.B
  host.io.cmd.bits  := 0.U.asTypeOf(host.io.cmd.bits)
  host.io.rsp.ready := false.B

  val readDataReg = RegInit(0.U(p.dataBits.W))
  val readRespReg = RegInit(AxiResp.OKAY)

  switch(state) {
    is(sWriteCmd) {
      host.io.cmd.valid      := true.B
      host.io.cmd.bits.write := true.B
      host.io.cmd.bits.addr  := 0.U
      host.io.cmd.bits.wdata := "h1234ABCD".U
      host.io.cmd.bits.strb  := Fill(p.strobeBits, 1.U(1.W))
      host.io.cmd.bits.prot  := 0.U
      when(host.io.cmd.fire) { state := sWaitWriteRsp }
    }
    is(sWaitWriteRsp) {
      host.io.rsp.ready := true.B
      when(host.io.rsp.fire) { state := sReadCmd }
    }
    is(sReadCmd) {
      host.io.cmd.valid      := true.B
      host.io.cmd.bits.write := false.B
      host.io.cmd.bits.addr  := 0.U
      host.io.cmd.bits.wdata := 0.U
      host.io.cmd.bits.strb  := 0.U
      host.io.cmd.bits.prot  := 0.U
      when(host.io.cmd.fire) { state := sWaitReadRsp }
    }
    is(sWaitReadRsp) {
      host.io.rsp.ready := true.B
      when(host.io.rsp.fire) {
        readDataReg := host.io.rsp.bits.rdata
        readRespReg := host.io.rsp.bits.resp
        state := sDone
      }
    }
    is(sDone) { host.io.rsp.ready := true.B }
  }

  io.done     := (state === sDone)
  io.readData := readDataReg
  io.readResp := readRespReg
}

// mill -i chisel.runMain soc.perip.mem.AXIRAMExample --target-dir build/rtl
object AXIRAMExample extends App {
  val firtoolOptions = Array(
    "--lowering-options=" + List(
      "disallowLocalVariables",
      "disallowPackedArrays",
      "locationInfoStyle=wrapInAtSquareBracket"
    ).reduce(_ + "," + _)
  )
  _root_.circt.stage.ChiselStage.emitSystemVerilogFile(new AXIRAMExample, args, firtoolOptions)
}
