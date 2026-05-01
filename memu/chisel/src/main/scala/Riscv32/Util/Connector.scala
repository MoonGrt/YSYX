package riscv.util

import chisel3._
import chisel3.util._
import chisel3.internal._

sealed trait ConnectMode
case object WireMode extends ConnectMode
case object RegMode  extends ConnectMode
object Connector {
  private object Impl {
    def toBiConnectMode(mode: ConnectMode): BiConnectSmart.ConnectMode = mode match {
      case WireMode => BiConnectSmart.WireMode
      case RegMode  => BiConnectSmart.RegMode
    }
  }
  def apply(in: Data, out: Data, mode: ConnectMode = WireMode): Unit = {
    BiConnectSmart.connect(in, out, Impl.toBiConnectMode(mode))
  }
  implicit class WireConnector(a: Data) {
    def <->(b: => Data): Unit = {
      Connector(a, b, WireMode)
    }
  }
  implicit class RegConnector(a: Data) {
    def <=>(b: => Data): Unit = {
      Connector(a, b, RegMode)
    }
  }
}




// Example
import Connector._
class Bus extends Bundle {
  val data = UInt(32.W)
}
class SrcModule extends Module {
  val io = IO(new Bundle {
    val out = Decoupled(new Bus)
  })
  io.out.valid := io.out.ready
  io.out.bits.data := 42.U
  dontTouch(io.out)
}
class SinkModule extends Module {
  val io = IO(new Bundle {
    val in = Flipped(Decoupled(new Bus))
  })
  val regData = RegInit(0.U(32.W))
  io.in.ready := true.B
  dontTouch(io.in)
  when(io.in.fire) {
    regData := io.in.bits.data
  }
}
class WireConnect extends Module {
  val src = Module(new SrcModule)
  val sink = Module(new SinkModule)
  // Connector(src.io.out, sink.io.in, WireMode)
  src.io.out <-> sink.io.in
}
class RegConnect extends Module {
  val src = Module(new SrcModule)
  val sink = Module(new SinkModule)
  // Connector(src.io.out, sink.io.in, RegMode)
  src.io.out <=> sink.io.in
}
