package riscv.e

import chisel3._
import chisel3.util._
import riscv.Constants.Riscv32E._
import peripheral.mem._

// ---------------------------
// Riscv32E CPU
// ---------------------------
class Riscv32E extends Module {
  val io = IO(new Bundle {
    val inst = new InstBus(DataWidth)
    val data = new DataBus(DataWidth)
  })
  // Modules
  val ifu = Module(new IFU)
  val idu = Module(new IDU)
  val exu = Module(new EXU)
  val lsu = Module(new LSU)
  val wbu = Module(new WBU)
  // Connect
  io.inst    <> ifu.io.ibus
  io.data    <> lsu.io.dbus
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
  val delayCfg = MemDelayConfig(
      enable = false,
      delayWidth = 8,
      delaySeed = 2,
      delayTaps = 0x9
    )
  // Modules
  val cpu = Module(new Riscv32E)
  val rom = Module(new ROM(useDpi = true, delayCfg = delayCfg))
  val ram = Module(new RAM(useDpi = true, delayCfg = delayCfg))
  // Inst
  rom.io  <> cpu.io.inst
  // Data
  ram.io  <> cpu.io.data
}
