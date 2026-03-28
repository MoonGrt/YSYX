package riscv.e

import chisel3._
import chisel3.util._
import riscv.Constants._
import riscv.Constants.Riscv32E._

// ----------------------------------
// LSU 模块: Load/Store Unit
// ----------------------------------
class LSU extends Module {
  val io = IO(new Bundle {
    val memsel = Input(MEM())
    val addr   = Input(UInt(DataWidth.W))
    val data   = Input(UInt(DataWidth.W))

    val memRen   = Output(Bool())                 // read enable
    val memWen   = Output(Bool())                 // write enable
    val memLen   = Output(UInt((DataWidth/8).W))  // length
    val memAddr  = Output(UInt(DataWidth.W))
    val memWdata = Output(UInt(DataWidth.W))
  })
  io.memRen   := !reset.asBool && io.memsel.isOneOf(MEM.RW, MEM.RH, MEM.RB, MEM.RHU, MEM.RBU)
  io.memWen   := !reset.asBool && io.memsel.isOneOf(MEM.WW, MEM.WH, MEM.WB)
  io.memAddr  := io.addr
  io.memWdata := io.data
  io.memLen   := Mux(io.memsel.isOneOf(MEM.WB, MEM.RB, MEM.RBU), 1.U,
                     Mux(io.memsel.isOneOf(MEM.WH, MEM.RH, MEM.RHU), 2.U, 4.U))
}
