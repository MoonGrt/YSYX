package riscv.util

import chisel3._
import chisel3.util._

object StageConnect {
  def apply[T <: Data](left: DecoupledIO[T], right: DecoupledIO[T], mode: String = "Wire") = {
    mode match {
      case "Wire"  => { right <> left }
      case "Reg"   => { right <> RegEnable(left, left.fire) }
      case "Queue" => { right <> Queue(left, 16) }
      case _ => throw new IllegalArgumentException(s"Unknown mode: $mode")
    }
  }
}

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
}

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
  Connector(src.io.out, sink.io.in, WireMode)
}
class RegConnect extends Module {
  val src = Module(new SrcModule)
  val sink = Module(new SinkModule)
  Connector(src.io.out, sink.io.in, RegMode)
}
