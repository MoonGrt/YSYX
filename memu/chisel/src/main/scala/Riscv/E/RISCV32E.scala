package soc.riscv.e

import chisel3._
import chisel3.util._
import soc.riscv.Constants.Riscv32E._
import soc.riscv.Parameters.Riscv32E._
import soc.perip.mem._
import soc.perip.uart._
import soc.perip.clint._
import bus.amba.axi.common._
import bus.amba.axi.axifull._

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
  axi.ar.valid       := (state === sIdle) && ibus.req.valid
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

  val sIdle :: sReadAddr :: sReadResp :: sWriteReq :: sWriteResp :: Nil = Enum(5)
  val state = RegInit(sIdle)

  val reqReg = Reg(new DataReq(p.dataBits))
  val awDone = RegInit(true.B)
  val wDone  = RegInit(true.B)

  // ----------------------------------------------------------------
  // Defaults
  // ----------------------------------------------------------------
  axi.ar.valid := false.B
  axi.aw.valid := false.B
  axi.w.valid  := false.B
  axi.r.ready := false.B
  axi.b.ready := false.B
  axi.ar.bits := DontCare
  axi.aw.bits := DontCare
  axi.w.bits  := DontCare
  dbus.req.ready := false.B
  dbus.resp.valid := false.B
  dbus.resp.bits.rdata := 0.U

  // ----------------------------------------------------------------
  // Common AXI fields
  // ----------------------------------------------------------------
  def fillAR(): Unit = {
    axi.ar.bits.id     := 0.U
    axi.ar.bits.addr   := reqReg.addr
    axi.ar.bits.len    := 0.U
    axi.ar.bits.size   := log2Ceil(p.dataBits / 8).U
    axi.ar.bits.burst  := 1.U
    axi.ar.bits.lock   := 0.U
    axi.ar.bits.cache  := 0.U
    axi.ar.bits.prot   := 0.U
    axi.ar.bits.qos    := 0.U
    axi.ar.bits.region := 0.U
    axi.ar.bits.user   := 0.U
  }
  def fillAW(): Unit = {
    axi.aw.bits.id     := 0.U
    axi.aw.bits.addr   := reqReg.addr
    axi.aw.bits.len    := 0.U
    axi.aw.bits.size   := log2Ceil(p.dataBits / 8).U
    axi.aw.bits.burst  := 1.U
    axi.aw.bits.lock   := 0.U
    axi.aw.bits.cache  := 0.U
    axi.aw.bits.prot   := 0.U
    axi.aw.bits.qos    := 0.U
    axi.aw.bits.region := 0.U
    axi.aw.bits.user   := 0.U
  }
  def fillW(): Unit = {
    axi.w.bits.data := reqReg.wdata
    axi.w.bits.strb := reqReg.mask
    axi.w.bits.last := true.B
    axi.w.bits.user := 0.U
  }

  // ----------------------------------------------------------------
  // Idle
  // ----------------------------------------------------------------
  when(state === sIdle) {
    dbus.req.ready := true.B
    when(dbus.req.fire) {
      reqReg := dbus.req.bits
      when(dbus.req.bits.ren) {
        state := sReadAddr
      }
      when(dbus.req.bits.wen) {
        awDone := false.B
        wDone  := false.B
        state  := sWriteReq
      }
    }
  }

  // ----------------------------------------------------------------
  // Read Address
  // ----------------------------------------------------------------
  when(state === sReadAddr) {
    axi.ar.valid := true.B
    fillAR()
    when(axi.ar.fire) {
      state := sReadResp
    }
  }

  // ----------------------------------------------------------------
  // Read Response
  // ----------------------------------------------------------------
  when(state === sReadResp) {
    dbus.resp.valid := axi.r.valid
    dbus.resp.bits.rdata := axi.r.bits.data
    axi.r.ready := dbus.resp.ready
    when(axi.r.fire) {
      state := sIdle
    }
  }

  // ----------------------------------------------------------------
  // Write Request
  // ----------------------------------------------------------------
  when(state === sWriteReq) {
    // ---------------- AW ----------------
    axi.aw.valid := !awDone
    fillAW()
    when(axi.aw.fire) {
      awDone := true.B
    }
    // ---------------- W ----------------
    axi.w.valid := !wDone
    fillW()
    when(axi.w.fire) {
      wDone := true.B
    }
    // ---------------- Finish ----------------
    when(awDone && wDone) {
      // state := sWriteResp
      state := sIdle  // 暂时不需要知道写入内存是否成功
    }
  }

  // ----------------------------------------------------------------
  // Write Response
  // ----------------------------------------------------------------
  axi.b.ready := true.B  // 暂时不需要知道写入内存是否成功
  when(state === sWriteResp) {
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
    masters = Seq(AXI4MasterParameters(name = "cpu_master", id = IdRange(0, 4)))
  )
  private val slavePort = AXI4SlavePortParameters(
    slaves = Seq(
      AXI4SlaveParameters(
        address = Seq(AddressSet(base = 0x80000000L, mask = 0xffffff)),
        supportsWrite = TransferSizes(0, 4),
        supportsRead = TransferSizes(0, 4)
      ),
      AXI4SlaveParameters(
        address = Seq(AddressSet(base = 0xa0000000L, mask = 0xfff)),
        supportsWrite = TransferSizes(0, 4),
        supportsRead = TransferSizes(0, 4)
      ),
      AXI4SlaveParameters(
        address = Seq(AddressSet(base = 0xb0000000L, mask = 0xfff)),
        supportsWrite = TransferSizes(0, 4),
        supportsRead = TransferSizes(0, 4)
      ),
    ),
    beatBytes = 4
  )
  private implicit val params: AxiParameters =
    new WithAxiPorts(masterPort, slavePort) ++ new BaseAxiConfig
  private val p: AxiParams = AxiParams.fromPortParameters


  // Core
  val cpu = Module(new Riscv32E(p))
  // SRAM
  if (memBusType == BusType.AXI) {
    // Xbar
    val xbar = Module(
      new AxiCrossbar(
        p = p,
        nMasters = 2,
        slaveAddress = Seq(
          AddressSet(0x80000000L, 0xffffff),
          AddressSet(0xa0000000L, 0xfff),
          AddressSet(0xb0000000L, 0xfff),
        )
      )
    )
    // SRAM
    val sram  = Module(new AXIRAM(p, useDpi = memUseDpi, delayCfg = memDelayCfg))
    val uart  = Module(new AXIUART(p))
    val clint = Module(new AXICLINT(p))
    // master 0 -> inst
    xbar.io.fromMasters(0) <> cpu.io.inst
    // master 1 -> data
    xbar.io.fromMasters(1) <> cpu.io.data
    // slave 0 -> sram
    sram.io  <> xbar.io.toSlaves(0)
    uart.io  <> xbar.io.toSlaves(1)
    clint.io <> xbar.io.toSlaves(2)
  } else {
    // Inst
    val rom = Module(new ROM(useDpi = memUseDpi, delayCfg = memDelayCfg))
    rom.io <> cpu.io.inst
    // Data
    val ram = Module(new RAM(useDpi = memUseDpi, delayCfg = memDelayCfg))
    ram.io <> cpu.io.data
  }
}
