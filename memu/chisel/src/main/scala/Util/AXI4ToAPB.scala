package soc.util

import chisel3._
import chisel3.util._

import org.chipsalliance.cde.config.Parameters
import freechips.rocketchip.amba._
import freechips.rocketchip.amba.axi4._
import freechips.rocketchip.amba.apb._
import freechips.rocketchip.diplomacy._
import freechips.rocketchip.util._

case class AXI4ToAPBNode()(implicit valName: ValName) extends MixedAdapterNode(AXI4Imp, APBImp)(
  dFn = { mp =>
    APBMasterPortParameters(
      masters = mp.masters.map { m => APBMasterParameters(name = m.name, nodePath = m.nodePath) },
      requestFields = mp.requestFields.filter(!_.isInstanceOf[AMBAProtField]),
      responseKeys  = mp.responseKeys
    )
  },
  uFn = { sp =>
    val beatBytes = 4
    AXI4SlavePortParameters(
    slaves = sp.slaves.map { s =>
      val maxXfer = TransferSizes(1, beatBytes)
      require(beatBytes == 4) // only support 8-byte data AXI
      AXI4SlaveParameters(
        address       = s.address,
        resources     = s.resources,
        regionType    = s.regionType,
        executable    = s.executable,
        nodePath      = s.nodePath,
        supportsWrite = if (s.supportsWrite) TransferSizes(1, beatBytes) else TransferSizes.none,
        supportsRead  = if (s.supportsRead)  TransferSizes(1, beatBytes) else TransferSizes.none,
        interleavedId = Some(0))}, // never interleaves D beats
    beatBytes = beatBytes,
    responseFields = sp.responseFields,
    requestKeys    = sp.requestKeys.filter(_ != AMBAProt))
  }
)

class AXI4ToAPB(val aFlow: Boolean = true)(implicit p: Parameters) extends LazyModule {
  val node = AXI4ToAPBNode()

  lazy val module = new LazyModuleImp(this) {
    (node.in zip node.out) foreach { case ((in, edgeIn), (out, edgeOut)) =>
      val (ar, r, aw, w, b) = (in.ar, in.r, in.aw, in.w, in.b)

      val sIdle :: sSetup :: sAccess :: sResponse :: Nil = Enum(4)
      val state = RegInit(sIdle)
      val isWrite = RegInit(false.B)
      val awHeld = RegInit(false.B)
      val wHeld = RegInit(false.B)

      // burst is not supported
      assert(!(ar.valid && ar.bits.len =/= 0.U))
      assert(!(aw.valid && aw.bits.len =/= 0.U))
      // size > 4 is not supported
      assert(!(ar.valid && ar.bits.size > "b10".U))
      assert(!(aw.valid && aw.bits.size > "b10".U))

      val ridReg = Reg(ar.bits.id.cloneType)
      val bidReg = Reg(aw.bits.id.cloneType)
      val araddrReg = RegInit(0.U(ar.bits.addr.getWidth.W))
      val awaddrReg = RegInit(0.U(aw.bits.addr.getWidth.W))
      val wdataReg = RegInit(0.U(w.bits.data.getWidth.W))
      val wstrbReg = RegInit(0.U(w.bits.strb.getWidth.W))
      val rdataReg = RegInit(0.U(out.prdata.getWidth.W))
      val respReg = RegInit(AXI4Parameters.RESP_OKAY)

      val canRead = state === sIdle && !awHeld && !wHeld
      ar.ready := canRead
      val takeRead = ar.fire
      val readSelected = canRead && ar.valid
      aw.ready := state === sIdle && !awHeld && !readSelected
      w.ready := state === sIdle && !wHeld && !readSelected

      when(state === sIdle) {
        when(takeRead) {
          ridReg := ar.bits.id
          araddrReg := ar.bits.addr
          isWrite := false.B
          state := sSetup
        }.otherwise {
          when(aw.fire) {
            bidReg := aw.bits.id
            awaddrReg := aw.bits.addr
            awHeld := true.B
          }
          when(w.fire) {
            wdataReg := w.bits.data
            wstrbReg := w.bits.strb
            wHeld := true.B
          }
          when((awHeld || aw.fire) && (wHeld || w.fire)) {
            isWrite := true.B
            awHeld := false.B
            wHeld := false.B
            state := sSetup
          }
        }
      }

      when(state === sSetup) {
        state := sAccess
      }
      when(state === sAccess && out.pready) {
        rdataReg := out.prdata
        respReg := Mux(out.pslverr,
          AXI4Parameters.RESP_SLVERR, AXI4Parameters.RESP_OKAY)
        state := sResponse
      }
      when(state === sResponse && (r.fire || b.fire)) {
        state := sIdle
      }

      out.psel    := state === sSetup || state === sAccess
      out.penable := state === sAccess
      out.pwrite  := isWrite
      out.paddr   := Mux(isWrite, awaddrReg, araddrReg)
      out.pprot   := APBParameters.PROT_DEFAULT
      out.pwdata  := wdataReg
      out.pstrb   := Mux(isWrite, wstrbReg, 0.U)

      r.valid  := state === sResponse && !isWrite
      r.bits.data := rdataReg
      r.bits.id   := ridReg
      r.bits.resp := respReg
      r.bits.last := true.B

      b.valid  := state === sResponse && isWrite
      b.bits.resp := respReg
      b.bits.id   := bidReg
    }
  }
}

object AXI4ToAPB {
  def apply(aFlow: Boolean = true)(implicit p: Parameters) = {
    val axi42apb = LazyModule(new AXI4ToAPB(aFlow))
    axi42apb.node
  }
}
