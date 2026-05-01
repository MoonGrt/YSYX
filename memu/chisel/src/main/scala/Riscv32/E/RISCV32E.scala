package riscv.e

import chisel3._
import chisel3.util._
import riscv.Constants._
import riscv.Constants.Riscv32E._
import riscv.util._

// ---------------------------
// Riscv32E CPU
// ---------------------------
// Inst Bus
class InstReq extends Bundle {
  val addr = UInt(DataWidth.W)
}
class InstResp extends Bundle {
  val data = UInt(DataWidth.W)
}
class InstBus extends Bundle {
  val req  = Decoupled(new InstReq)
  val resp = Flipped(Decoupled(new InstResp))
}
// Data Bus
class DataReq extends Bundle {
  val ren   = Bool()
  val wen   = Bool()
  val mask  = UInt((DataWidth/8).W)
  val addr  = UInt(DataWidth.W)
  val wdata = UInt(DataWidth.W)
}
class DataResp extends Bundle {
  val rdata = UInt(DataWidth.W)
}
class DataBus extends Bundle {
  val req  = Decoupled(new DataReq)
  val resp = Flipped(Decoupled(new DataResp))
}
class Riscv32E extends Module {
  val io = IO(new Bundle {
    val inst = new InstBus
    val data = new DataBus
  })

  // Modules
  val ifu = Module(new IFU)
  val idu = Module(new IDU)
  val exu = Module(new EXU)
  val lsu = Module(new LSU)
  val wbu = Module(new WBU)

  import riscv.util.Connector._

  // Bus
  io.inst <-> ifu.io.ibus
  io.data <-> lsu.io.dbus

  // Units
  ifu.io.in    <-> exu.io.br
  idu.io.ifuin <-> ifu.io.out
  idu.io.wbuin <-> wbu.io.out
  exu.io.in    <-> idu.io.out
  lsu.io.in    <-> exu.io.out
  wbu.io.in    <-> lsu.io.out
}

// ---------------------------
// Riscv32E TOP = CPU + ROM + RAM
// ---------------------------
// import peripheral._
class Riscv32ETOP extends Module {
  val cpu = Module(new Riscv32E)
  val rom = Module(new ROM_DPI)
  val ram = Module(new RAM_DPI)
  // val rom = Module(new ROM(depth = 256, dataWidth = 32))
  // val ram = Module(new RAM(depth = 256, dataWidth = 32))
  // Inst
  rom.io.clk        <> clock
  rom.io.req_ready  <> cpu.io.inst.req.ready
  rom.io.addr       <> cpu.io.inst.req.bits.addr
  rom.io.req_valid  <> cpu.io.inst.req.valid
  rom.io.resp_ready <> cpu.io.inst.resp.ready
  rom.io.data       <> cpu.io.inst.resp.bits.data
  rom.io.resp_valid <> cpu.io.inst.resp.valid
  // Data
  ram.io.clk   <> clock
  ram.io.req_ready  <> cpu.io.data.req.ready
  ram.io.ren        <> cpu.io.data.req.bits.ren
  ram.io.wen        <> cpu.io.data.req.bits.wen
  ram.io.mask       <> cpu.io.data.req.bits.mask
  ram.io.addr       <> cpu.io.data.req.bits.addr
  ram.io.wdata      <> cpu.io.data.req.bits.wdata
  ram.io.req_valid  <> cpu.io.data.req.valid
  ram.io.resp_ready <> cpu.io.data.resp.ready
  ram.io.rdata      <> cpu.io.data.resp.bits.rdata
  ram.io.resp_valid <> cpu.io.data.resp.valid     
}
