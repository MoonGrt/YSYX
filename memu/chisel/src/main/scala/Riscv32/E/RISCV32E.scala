package riscv.e

import chisel3._
import chisel3.util._
import riscv.Constants.Riscv32E._
import riscv.Parameters.Riscv32E._
import peripheral.mem._
import bus.amba.axi.common._

// ----------------------------------
// Bus Bridge
// ----------------------------------
class IBusBridge(p: AxiParams) extends Module {
  val axi  = IO(new AXI4MasterBundle(p))
  val ibus = IO(Flipped(new InstBus(p.dataBits)))

  val sIdle :: sWait :: Nil = Enum(2)
  val state = RegInit(sIdle)

  // Default
  axi.aw.valid := false.B
  axi.aw.bits  := DontCare
  axi.w.valid  := false.B
  axi.w.bits   := DontCare
  axi.b.ready  := false.B

  // AR Channel
  axi.ar.valid := (state === sIdle) && ibus.req.valid

  axi.ar.bits.id     := 0.U
  axi.ar.bits.addr   := ibus.req.bits.addr
  axi.ar.bits.len    := 0.U
  axi.ar.bits.size   := log2Ceil(p.dataBits / 8).U
  axi.ar.bits.burst  := 1.U // INCR
  axi.ar.bits.lock   := 0.U
  axi.ar.bits.cache  := 0.U
  axi.ar.bits.prot   := 0.U
  axi.ar.bits.qos    := 0.U
  axi.ar.bits.region := 0.U
  axi.ar.bits.user   := 0.U

  ibus.req.ready := (state === sIdle) && axi.ar.ready

  // R Channel
  ibus.resp.valid := (state === sWait) && axi.r.valid
  ibus.resp.bits.data := axi.r.bits.data
  axi.r.ready := (state === sWait) && ibus.resp.ready

  // State
  switch(state) {
    is(sIdle) {
      when(ibus.req.fire) {
        state := sWait
      }
    }
    is(sWait) {
      when(axi.r.fire) {
        state := sIdle
      }
    }
  }
}

class DBusBridge(p: AxiParams) extends Module {
  val axi  = IO(new AXI4MasterBundle(p))
  val dbus = IO(Flipped(new DataBus(p.dataBits)))

  val sIdle :: sReadResp :: sWriteResp :: Nil = Enum(3)
  val state = RegInit(sIdle)

  val reqReg = Reg(new DataReq(p.dataBits))

  // Default

  axi.ar.valid := false.B
  axi.aw.valid := false.B
  axi.w.valid  := false.B

  axi.b.ready := false.B
  axi.r.ready := false.B

  axi.ar.bits := DontCare
  axi.aw.bits := DontCare
  axi.w.bits  := DontCare

  dbus.req.ready := false.B

  dbus.resp.valid := false.B
  dbus.resp.bits.rdata := axi.r.bits.data

  // Idle
  when(state === sIdle) {
    dbus.req.ready := true.B

    // ---------- Read ----------
    when(dbus.req.valid && dbus.req.bits.ren) {
      axi.ar.valid := true.B

      axi.ar.bits.id     := 0.U
      axi.ar.bits.addr   := dbus.req.bits.addr
      axi.ar.bits.len    := 0.U
      axi.ar.bits.size   := log2Ceil(p.dataBits / 8).U
      axi.ar.bits.burst  := 1.U
      axi.ar.bits.lock   := 0.U
      axi.ar.bits.cache  := 0.U
      axi.ar.bits.prot   := 0.U
      axi.ar.bits.qos    := 0.U
      axi.ar.bits.region := 0.U
      axi.ar.bits.user   := 0.U

      when(axi.ar.ready) {
        reqReg := dbus.req.bits
        state := sReadResp
      }
    }

    // ---------- Write ----------
    when(dbus.req.valid && dbus.req.bits.wen) {
      axi.aw.valid := true.B
      axi.w.valid  := true.B

      // AW
      axi.aw.bits.id     := 0.U
      axi.aw.bits.addr   := dbus.req.bits.addr
      axi.aw.bits.len    := 0.U
      axi.aw.bits.size   := log2Ceil(p.dataBits / 8).U
      axi.aw.bits.burst  := 1.U
      axi.aw.bits.lock   := 0.U
      axi.aw.bits.cache  := 0.U
      axi.aw.bits.prot   := 0.U
      axi.aw.bits.qos    := 0.U
      axi.aw.bits.region := 0.U
      axi.aw.bits.user   := 0.U

      // W
      axi.w.bits.data := dbus.req.bits.wdata
      axi.w.bits.strb := dbus.req.bits.mask
      axi.w.bits.last := true.B
      axi.w.bits.user := 0.U
      when(axi.aw.ready && axi.w.ready) {
        reqReg := dbus.req.bits
        state := sWriteResp
      }
    }
  }

  // Read Response
  when(state === sReadResp) {
    dbus.resp.valid := axi.r.valid
    dbus.resp.bits.rdata := axi.r.bits.data
    axi.r.ready := dbus.resp.ready
    when(axi.r.fire) {
      state := sIdle
    }
  }

  // Write Response
  when(state === sWriteResp) {
    axi.b.ready := true.B
    dbus.resp.valid := axi.b.valid
    dbus.resp.bits.rdata := 0.U
    when(axi.b.fire) {
      state := sIdle
    }
  }
}

// ---------------------------
// Riscv32E CPU
// ---------------------------
class Riscv32E(p: AxiParams) extends Module {
  val io = IO(new Bundle {
    val inst = if (memBusType == BusType.AXI) {
        new AXI4MasterBundle(p)
      } else {
        new InstBus(DataWidth)
      }
    val data = if (memBusType == BusType.AXI) {
        new AXI4MasterBundle(p)
      } else {
        new DataBus(DataWidth)
      }
  })
  dontTouch(io.inst)
  dontTouch(io.data)
  // Modules
  val ifu = Module(new IFU)
  val idu = Module(new IDU)
  val exu = Module(new EXU)
  val lsu = Module(new LSU)
  val wbu = Module(new WBU)
  // Connect
  if (memBusType == BusType.AXI) {
    val iBridge = Module(new IBusBridge(p))
    iBridge.ibus <> ifu.io.ibus
    iBridge.axi <> io.inst
    val dBridge = Module(new DBusBridge(p))
    dBridge.dbus <> lsu.io.dbus
    dBridge.axi <> io.data
  } else {
    io.inst <> ifu.io.ibus
    io.data <> lsu.io.dbus
  }
  // Connect
  exu.io.br  <> ifu.io.in
  ifu.io.out <> idu.io.ifuin
  wbu.io.out <> idu.io.wbuin
  idu.io.out <> exu.io.in
  exu.io.out <> lsu.io.in
  lsu.io.out <> wbu.io.in
}

// ---------------------------
// Riscv32E TOP = CPU + ROM + RAM
// ---------------------------
class Riscv32ETOP extends Module {

  private val masterPort = AXI4MasterPortParameters(
    masters = Seq(AXI4MasterParameters(name = "axi4ram-example-master", id = IdRange(0, 4)))
  )
  private val slavePort = AXI4SlavePortParameters(
    slaves = Seq(
      AXI4SlaveParameters(
        address = Seq(AddressSet(base = 0x80000000L, size = 1024)),
        supportsWrite = TransferSizes(1, 4),
        supportsRead = TransferSizes(1, 4)
      )
    ),
    beatBytes = 4
  )
  private implicit val params: AxiParameters =
    new WithAxiPorts(masterPort, slavePort) ++ new BaseAxiConfig
  private val p: AxiParams = AxiParams.fromPortParameters


  val delayCfg = MemDelayConfig(
      enable = false,
      delayWidth = 8,
      delaySeed = 2,
      delayTaps = 0x9
    )
  // Core
  val cpu = Module(new Riscv32E(p))
  // Inst
  if (memBusType == BusType.AXI) {
    val rom = Module(new AXIROM(p, useDpi = memUseDpi))
    rom.io <> cpu.io.inst
  } else {
    val rom = Module(new ROM(useDpi = memUseDpi, delayCfg = memDelayCfg))
    rom.io <> cpu.io.inst
  }
  // Data
  if (memBusType == BusType.AXI) {
    val ram = Module(new AXIRAM(p, useDpi = memUseDpi))
    ram.io <> cpu.io.data
  } else {
    val ram = Module(new RAM(useDpi = memUseDpi, delayCfg = memDelayCfg))
    ram.io <> cpu.io.data
  }
}
