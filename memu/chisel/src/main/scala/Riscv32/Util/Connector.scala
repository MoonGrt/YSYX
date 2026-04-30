package riscv.util

import chisel3._
import chisel3.util._

// ==============================
// Connect Strategy Definition
// ==============================
sealed trait ConnMode
case object WireMode  extends ConnMode
case object RegMode   extends ConnMode
case object QueueMode extends ConnMode

// ==============================
// Connector
// ==============================
object Connector {
  def apply[T <: Data](in: T, mode: String): T = {
    val m = mode match {
      case "Wire"  => WireMode
      case "Reg"   => RegMode
      case "Queue" => QueueMode
      case _ => throw new IllegalArgumentException(s"Unknown mode: $mode")
    }
    apply(in, m)
  }
  def apply[T <: Data](in: T, out: T, mode: String): Unit = {
    val m = mode match {
      case "Wire"  => WireMode
      case "Reg"   => RegMode
      case "Queue" => QueueMode
      case _ => throw new IllegalArgumentException(s"Unknown mode: $mode")
    }
    apply(in, out, m)
  }
  // =========================================================
  // (A) 纯函数式接口：返回生成后的节点
  // =========================================================
  def apply[T <: Data](in: T, mode: ConnMode): T = {
    mode match {
      // ---------- Wire ----------
      case WireMode =>
        val out = Wire(chiselTypeOf(in))
        connectWire(in, out)
        out
      // ---------- Reg ----------
      case RegMode =>
        val out = Wire(chiselTypeOf(in))
        val reg = RegInit(0.U.asTypeOf(in))
        reg := in.asTypeOf(reg)
        out := reg
        out
      // ---------- Queue ----------
      case QueueMode =>
        val out = Wire(chiselTypeOf(in))
        val q = Module(new Queue(chiselTypeOf(in), 2))
        q.io.enq.bits  := in.asTypeOf(q.io.enq.bits)
        q.io.enq.valid := true.B
        out := q.io.deq.bits.asTypeOf(out)
        out
    }
  }
  // =========================================================
  // (B) in → out 直接连接版本
  // =========================================================
  def apply[T <: Data](in: T, out: T, mode: ConnMode): Unit = {
    mode match {
      // ---------- Wire ----------
      case WireMode =>
        connectWire(in, out)
      // ---------- Reg ----------
      case RegMode =>
        val reg = RegInit(0.U.asTypeOf(out))
        reg := in.asTypeOf(reg)
        out := reg
      // ---------- Queue ----------
      case QueueMode =>
        val q = Module(new Queue(chiselTypeOf(in), 2))
        q.io.enq.bits  := in.asTypeOf(q.io.enq.bits)
        q.io.enq.valid := true.B
        out := q.io.deq.bits.asTypeOf(out)
    }
  }
  // ==============================
  // Partial Connection (Custom Mapping)
  // ==============================
  trait PartialConnect[A <: Data, B <: Data] {
    def connect(a: A, b: B): Unit
  }
  def partial[A <: Data, B <: Data](a: A, b: B)(implicit pc: PartialConnect[A, B]): Unit = {
    pc.connect(a, b)
  }
  // ======================================================
  // 核心：支持 mixed Input/Output Bundle
  // ======================================================
  private def connectWire[T <: Data](in: T, out: T): Unit = {
    (in, out) match {
      case (_: Bundle, _: Bundle) =>
        out <> in
      case (_: UInt, _: UInt) =>
        out := in
      case (_: Vec[_], _: Vec[_]) =>
        out <> in
      case _ =>
        out := in.asTypeOf(out)
    }
  }
}

/*
// ==============================
// Example Module Usage
// ==============================
Connector(io.ibus, io.obus, WireMode)
io.obus <> Connector(io.ibus, WireMode)
*/
