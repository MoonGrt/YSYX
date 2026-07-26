package soc.util

import chisel3._
import chisel3.util._
import freechips.rocketchip.amba.axi4.{AXI4Bundle, AXI4BundleParameters}
import soc.perip.mem.{DataBus, DataReq, InstBus}
import bus.amba.axi.common.{AxiParams, AXI4MasterBundle => CustomAXI4MasterBundle}

/** Instruction-bus adapter using MEMU's standalone AXI4 bundle. */
class IBusBridge(p: AxiParams) extends Module {
  val axi  = IO(new CustomAXI4MasterBundle(p))
  val ibus = IO(Flipped(new InstBus(p.dataBits)))

  val idle :: waitResp :: Nil = Enum(2)
  val state = RegInit(idle)

  axi.aw.valid := false.B
  axi.aw.bits := DontCare
  axi.w.valid := false.B
  axi.w.bits := DontCare
  axi.b.ready := false.B

  axi.ar.valid := state === idle && ibus.req.valid
  axi.ar.bits := DontCare
  axi.ar.bits.id := 0.U
  axi.ar.bits.addr := ibus.req.bits.addr
  axi.ar.bits.len := 0.U
  axi.ar.bits.size := log2Ceil(p.dataBits / 8).U
  axi.ar.bits.burst := 1.U
  axi.ar.bits.lock := 0.U
  axi.ar.bits.cache := 0.U
  axi.ar.bits.prot := 0.U
  axi.ar.bits.qos := 0.U
  axi.ar.bits.region := 0.U
  axi.ar.bits.user := 0.U

  ibus.req.ready := state === idle && axi.ar.ready
  ibus.resp.valid := state === waitResp && axi.r.valid
  ibus.resp.bits.data := axi.r.bits.data
  axi.r.ready := state === waitResp && ibus.resp.ready

  when(state === idle && ibus.req.fire) { state := waitResp }
  when(state === waitResp && axi.r.fire) { state := idle }
}

/** Data-bus adapter using MEMU's standalone AXI4 bundle. */
class DBusBridge(p: AxiParams) extends Module {
  val axi  = IO(new CustomAXI4MasterBundle(p))
  val dbus = IO(Flipped(new DataBus(p.dataBits)))

  val idle :: readAddr :: readResp :: writeReq :: writeResp :: Nil = Enum(5)
  val state = RegInit(idle)
  val request = Reg(new DataReq(p.dataBits))
  val awDone = RegInit(false.B)
  val wDone = RegInit(false.B)

  axi.ar.valid := false.B
  axi.ar.bits := DontCare
  axi.aw.valid := false.B
  axi.aw.bits := DontCare
  axi.w.valid := false.B
  axi.w.bits := DontCare
  axi.r.ready := false.B
  axi.b.ready := false.B
  dbus.req.ready := false.B
  dbus.resp.valid := false.B
  dbus.resp.bits.rdata := 0.U

  when(state === idle) {
    dbus.req.ready := true.B
    when(dbus.req.fire) {
      request := dbus.req.bits
      when(dbus.req.bits.ren) { state := readAddr }
      when(dbus.req.bits.wen) {
        awDone := false.B
        wDone := false.B
        state := writeReq
      }
    }
  }

  when(state === readAddr) {
    axi.ar.valid := true.B
    axi.ar.bits := DontCare
    axi.ar.bits.id := 0.U
    axi.ar.bits.addr := request.addr
    axi.ar.bits.len := 0.U
    axi.ar.bits.size := request.size
    axi.ar.bits.burst := 1.U
    axi.ar.bits.lock := 0.U
    axi.ar.bits.cache := 0.U
    axi.ar.bits.prot := 0.U
    axi.ar.bits.qos := 0.U
    axi.ar.bits.region := 0.U
    axi.ar.bits.user := 0.U
    when(axi.ar.fire) { state := readResp }
  }

  when(state === readResp) {
    dbus.resp.valid := axi.r.valid
    dbus.resp.bits.rdata := axi.r.bits.data
    axi.r.ready := dbus.resp.ready
    when(axi.r.fire) { state := idle }
  }

  when(state === writeReq) {
    axi.aw.valid := !awDone
    axi.aw.bits := DontCare
    axi.aw.bits.id := 0.U
    axi.aw.bits.addr := request.addr
    axi.aw.bits.len := 0.U
    axi.aw.bits.size := request.size
    axi.aw.bits.burst := 1.U
    axi.aw.bits.lock := 0.U
    axi.aw.bits.cache := 0.U
    axi.aw.bits.prot := 0.U
    axi.aw.bits.qos := 0.U
    axi.aw.bits.region := 0.U
    axi.aw.bits.user := 0.U

    axi.w.valid := !wDone
    axi.w.bits := DontCare
    axi.w.bits.data := request.wdata
    axi.w.bits.strb := request.mask
    axi.w.bits.last := true.B
    axi.w.bits.user := 0.U

    when(axi.aw.fire) { awDone := true.B }
    when(axi.w.fire) { wDone := true.B }
    when((awDone || axi.aw.fire) && (wDone || axi.w.fire)) {
      state := writeResp
    }
  }

  when(state === writeResp) {
    dbus.resp.valid := axi.b.valid
    dbus.resp.bits.rdata := 0.U
    axi.b.ready := dbus.resp.ready
    when(axi.b.fire) { state := idle }
  }
}

/** Boundary adapter used by the MEMU simulation top while the core itself
  * speaks rocket-chip AXI4. */
class RCToCustomAXI(rcp: AXI4BundleParameters, cp: AxiParams) extends Module {
  val io = IO(new Bundle {
    val rc = Flipped(new AXI4Bundle(rcp))
    val custom = new CustomAXI4MasterBundle(cp)
  })

  io.custom.aw.valid := io.rc.aw.valid
  io.rc.aw.ready := io.custom.aw.ready
  io.custom.aw.bits := DontCare
  io.custom.aw.bits.id := io.rc.aw.bits.id
  io.custom.aw.bits.addr := io.rc.aw.bits.addr
  io.custom.aw.bits.len := io.rc.aw.bits.len
  io.custom.aw.bits.size := io.rc.aw.bits.size
  io.custom.aw.bits.burst := io.rc.aw.bits.burst
  io.custom.aw.bits.lock := io.rc.aw.bits.lock
  io.custom.aw.bits.cache := io.rc.aw.bits.cache
  io.custom.aw.bits.prot := io.rc.aw.bits.prot
  io.custom.aw.bits.qos := io.rc.aw.bits.qos
  io.custom.aw.bits.region := 0.U
  io.custom.aw.bits.user := 0.U

  io.custom.w.valid := io.rc.w.valid
  io.rc.w.ready := io.custom.w.ready
  io.custom.w.bits := DontCare
  io.custom.w.bits.data := io.rc.w.bits.data
  io.custom.w.bits.strb := io.rc.w.bits.strb
  io.custom.w.bits.last := io.rc.w.bits.last
  io.custom.w.bits.user := 0.U

  io.rc.b.valid := io.custom.b.valid
  io.custom.b.ready := io.rc.b.ready
  io.rc.b.bits := DontCare
  io.rc.b.bits.id := io.custom.b.bits.id
  io.rc.b.bits.resp := io.custom.b.bits.resp

  io.custom.ar.valid := io.rc.ar.valid
  io.rc.ar.ready := io.custom.ar.ready
  io.custom.ar.bits := DontCare
  io.custom.ar.bits.id := io.rc.ar.bits.id
  io.custom.ar.bits.addr := io.rc.ar.bits.addr
  io.custom.ar.bits.len := io.rc.ar.bits.len
  io.custom.ar.bits.size := io.rc.ar.bits.size
  io.custom.ar.bits.burst := io.rc.ar.bits.burst
  io.custom.ar.bits.lock := io.rc.ar.bits.lock
  io.custom.ar.bits.cache := io.rc.ar.bits.cache
  io.custom.ar.bits.prot := io.rc.ar.bits.prot
  io.custom.ar.bits.qos := io.rc.ar.bits.qos
  io.custom.ar.bits.region := 0.U
  io.custom.ar.bits.user := 0.U

  io.rc.r.valid := io.custom.r.valid
  io.custom.r.ready := io.rc.r.ready
  io.rc.r.bits := DontCare
  io.rc.r.bits.id := io.custom.r.bits.id
  io.rc.r.bits.data := io.custom.r.bits.data
  io.rc.r.bits.resp := io.custom.r.bits.resp
  io.rc.r.bits.last := io.custom.r.bits.last
}

/** Boundary adapter used by diplomacy SoCs when the selected CPU boundary
  * speaks MEMU's standalone AXI4 bundle. */
class CustomToRCAXI(cp: AxiParams, rcp: AXI4BundleParameters) extends Module {
  val io = IO(new Bundle {
    val custom = Flipped(new CustomAXI4MasterBundle(cp))
    val rc = new AXI4Bundle(rcp)
  })

  io.rc.aw.valid := io.custom.aw.valid
  io.custom.aw.ready := io.rc.aw.ready
  io.rc.aw.bits := DontCare
  io.rc.aw.bits.id := io.custom.aw.bits.id
  io.rc.aw.bits.addr := io.custom.aw.bits.addr
  io.rc.aw.bits.len := io.custom.aw.bits.len
  io.rc.aw.bits.size := io.custom.aw.bits.size
  io.rc.aw.bits.burst := io.custom.aw.bits.burst
  io.rc.aw.bits.lock := io.custom.aw.bits.lock
  io.rc.aw.bits.cache := io.custom.aw.bits.cache
  io.rc.aw.bits.prot := io.custom.aw.bits.prot
  io.rc.aw.bits.qos := io.custom.aw.bits.qos

  io.rc.w.valid := io.custom.w.valid
  io.custom.w.ready := io.rc.w.ready
  io.rc.w.bits := DontCare
  io.rc.w.bits.data := io.custom.w.bits.data
  io.rc.w.bits.strb := io.custom.w.bits.strb
  io.rc.w.bits.last := io.custom.w.bits.last

  io.custom.b.valid := io.rc.b.valid
  io.rc.b.ready := io.custom.b.ready
  io.custom.b.bits := DontCare
  io.custom.b.bits.id := io.rc.b.bits.id
  io.custom.b.bits.resp := io.rc.b.bits.resp
  io.custom.b.bits.user := 0.U

  io.rc.ar.valid := io.custom.ar.valid
  io.custom.ar.ready := io.rc.ar.ready
  io.rc.ar.bits := DontCare
  io.rc.ar.bits.id := io.custom.ar.bits.id
  io.rc.ar.bits.addr := io.custom.ar.bits.addr
  io.rc.ar.bits.len := io.custom.ar.bits.len
  io.rc.ar.bits.size := io.custom.ar.bits.size
  io.rc.ar.bits.burst := io.custom.ar.bits.burst
  io.rc.ar.bits.lock := io.custom.ar.bits.lock
  io.rc.ar.bits.cache := io.custom.ar.bits.cache
  io.rc.ar.bits.prot := io.custom.ar.bits.prot
  io.rc.ar.bits.qos := io.custom.ar.bits.qos

  io.custom.r.valid := io.rc.r.valid
  io.rc.r.ready := io.custom.r.ready
  io.custom.r.bits := DontCare
  io.custom.r.bits.id := io.rc.r.bits.id
  io.custom.r.bits.data := io.rc.r.bits.data
  io.custom.r.bits.resp := io.rc.r.bits.resp
  io.custom.r.bits.last := io.rc.r.bits.last
  io.custom.r.bits.user := 0.U
}

/** Instruction-bus adapter using rocket-chip's native AXI4 bundle. */
class RCIBusBridge(p: AXI4BundleParameters) extends Module {
  val io = IO(new Bundle {
    val axi = new AXI4Bundle(p)
    val ibus = Flipped(new InstBus(p.dataBits))
  })

  val idle :: waitResp :: Nil = Enum(2)
  val state = RegInit(idle)

  io.axi.aw.valid := false.B
  io.axi.aw.bits := DontCare
  io.axi.w.valid := false.B
  io.axi.w.bits := DontCare
  io.axi.b.ready := false.B

  io.axi.ar.valid := state === idle && io.ibus.req.valid
  io.axi.ar.bits := DontCare
  io.axi.ar.bits.id := 0.U
  io.axi.ar.bits.addr := io.ibus.req.bits.addr
  io.axi.ar.bits.len := 0.U
  io.axi.ar.bits.size := log2Ceil(p.dataBits / 8).U
  io.axi.ar.bits.burst := 1.U
  io.axi.ar.bits.lock := 0.U
  io.axi.ar.bits.cache := 0.U
  io.axi.ar.bits.prot := 0.U
  io.axi.ar.bits.qos := 0.U

  io.ibus.req.ready := state === idle && io.axi.ar.ready
  io.ibus.resp.valid := state === waitResp && io.axi.r.valid
  io.ibus.resp.bits.data := io.axi.r.bits.data
  io.axi.r.ready := state === waitResp && io.ibus.resp.ready

  when(state === idle && io.ibus.req.fire) { state := waitResp }
  when(state === waitResp && io.axi.r.fire) { state := idle }
}

/** Data-bus adapter using rocket-chip's native AXI4 bundle. */
class RCDBusBridge(p: AXI4BundleParameters) extends Module {
  val io = IO(new Bundle {
    val axi = new AXI4Bundle(p)
    val dbus = Flipped(new DataBus(p.dataBits))
  })

  val idle :: readAddr :: readResp :: writeReq :: writeResp :: Nil = Enum(5)
  val state = RegInit(idle)
  val request = Reg(new DataReq(p.dataBits))
  val awDone = RegInit(false.B)
  val wDone = RegInit(false.B)

  io.axi.ar.valid := false.B
  io.axi.ar.bits := DontCare
  io.axi.aw.valid := false.B
  io.axi.aw.bits := DontCare
  io.axi.w.valid := false.B
  io.axi.w.bits := DontCare
  io.axi.r.ready := false.B
  io.axi.b.ready := false.B
  io.dbus.req.ready := false.B
  io.dbus.resp.valid := false.B
  io.dbus.resp.bits.rdata := 0.U

  when(state === idle) {
    io.dbus.req.ready := true.B
    when(io.dbus.req.fire) {
      request := io.dbus.req.bits
      when(io.dbus.req.bits.ren) { state := readAddr }
      when(io.dbus.req.bits.wen) {
        awDone := false.B
        wDone := false.B
        state := writeReq
      }
    }
  }

  when(state === readAddr) {
    io.axi.ar.valid := true.B
    io.axi.ar.bits := DontCare
    io.axi.ar.bits.id := 0.U
    io.axi.ar.bits.addr := request.addr
    io.axi.ar.bits.len := 0.U
    io.axi.ar.bits.size := request.size
    io.axi.ar.bits.burst := 1.U
    io.axi.ar.bits.lock := 0.U
    io.axi.ar.bits.cache := 0.U
    io.axi.ar.bits.prot := 0.U
    io.axi.ar.bits.qos := 0.U
    when(io.axi.ar.fire) { state := readResp }
  }

  when(state === readResp) {
    io.dbus.resp.valid := io.axi.r.valid
    io.dbus.resp.bits.rdata := io.axi.r.bits.data
    io.axi.r.ready := io.dbus.resp.ready
    when(io.axi.r.fire) { state := idle }
  }

  when(state === writeReq) {
    io.axi.aw.valid := !awDone
    io.axi.aw.bits := DontCare
    io.axi.aw.bits.id := 0.U
    io.axi.aw.bits.addr := request.addr
    io.axi.aw.bits.len := 0.U
    io.axi.aw.bits.size := request.size
    io.axi.aw.bits.burst := 1.U
    io.axi.aw.bits.lock := 0.U
    io.axi.aw.bits.cache := 0.U
    io.axi.aw.bits.prot := 0.U
    io.axi.aw.bits.qos := 0.U

    io.axi.w.valid := !wDone
    io.axi.w.bits := DontCare
    io.axi.w.bits.data := request.wdata
    io.axi.w.bits.strb := request.mask
    io.axi.w.bits.last := true.B

    when(io.axi.aw.fire) { awDone := true.B }
    when(io.axi.w.fire) { wDone := true.B }
    when((awDone || io.axi.aw.fire) && (wDone || io.axi.w.fire)) {
      state := writeResp
    }
  }

  when(state === writeResp) {
    io.dbus.resp.valid := io.axi.b.valid
    io.dbus.resp.bits.rdata := 0.U
    io.axi.b.ready := io.dbus.resp.ready
    when(io.axi.b.fire) { state := idle }
  }
}
