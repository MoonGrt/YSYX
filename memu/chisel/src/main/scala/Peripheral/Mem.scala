package peripheral

import chisel3._
import chisel3.util._

class ROM(
  val depth: Int,
  val dataWidth: Int,
  val initFile: Option[String] = None
) extends Module {
  val addrWidth = log2Ceil(depth)
  val io = IO(new Bundle {
    val addr = Input(UInt(addrWidth.W))
    val data = Output(UInt(dataWidth.W))
  })
  val mem = SyncReadMem(depth, UInt(dataWidth.W))
  io.data := mem.read(io.addr, true.B)
}

class RAM(
  val depth: Int,
  val dataWidth: Int
) extends Module {
  require(dataWidth % 8 == 0, "dataWidth must be multiple of 8")
  val addrWidth = log2Ceil(depth)
  val maskWidth = dataWidth / 8
  val io = IO(new Bundle {
    val ren   = Input(Bool())
    val wen   = Input(Bool())
    val mask  = Input(UInt(maskWidth.W))
    val addr  = Input(UInt(addrWidth.W))
    val wdata = Input(UInt(dataWidth.W))
    val rdata = Output(UInt(dataWidth.W))
  })
  val mem = SyncReadMem(depth, Vec(maskWidth, UInt(8.W)))
  val wdataVec = Wire(Vec(maskWidth, UInt(8.W)))
  for (i <- 0 until maskWidth) {
    wdataVec(i) := io.wdata(8*(i+1)-1, 8*i)
  }
  when(io.wen) {
    mem.write(io.addr, wdataVec, io.mask.asBools)
  }
  val rdataVec = mem.read(io.addr, io.ren)
  io.rdata := rdataVec.asUInt
}






