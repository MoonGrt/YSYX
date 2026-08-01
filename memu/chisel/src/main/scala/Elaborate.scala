// object MiniRVTop extends App {
//   val firtoolOptions = Array(
//     "--lowering-options=" + List(
//       // make yosys happy
//       // see https://github.com/llvm/circt/blob/main/docs/VerilogGeneration.md
//       "disallowLocalVariables",
//       "disallowPackedArrays",
//       "locationInfoStyle=wrapInAtSquareBracket"
//     ).reduce(_ + "," + _)
//   )
//   circt.stage.ChiselStage.emitSystemVerilogFile(new soc.riscv.mini.MiniRVTop(), args, firtoolOptions)
// }

object Riscv32ETop extends App {
  val firtoolOptions = Array(
    "--lowering-options=" + List(
      // make yosys happy
      // see https://github.com/llvm/circt/blob/main/docs/VerilogGeneration.md
      "disallowLocalVariables",
      "disallowPackedArrays",
      "locationInfoStyle=wrapInAtSquareBracket"
    ).reduce(_ + "," + _)
  )
  circt.stage.ChiselStage.emitSystemVerilogFile(new soc.riscv.e.Riscv32ETop, args, firtoolOptions)
}

object SoCTop extends App {
  implicit val config: org.chipsalliance.cde.config.Parameters =
    new org.chipsalliance.cde.config.Config(
      new freechips.rocketchip.system.Edge32BitConfig ++
      new freechips.rocketchip.system.DefaultRV32Config
    )
  val firtoolOptions = Array(
    // rocket-chip AXI4RAM emits SRAMAnnotation for downstream SRAM
    // replacement flows.  firtool does not consume this annotation itself.
    "--disable-annotation-unknown",
    "--lowering-options=" + List(
      // make yosys happy
      // see https://github.com/llvm/circt/blob/main/docs/VerilogGeneration.md
      "disallowLocalVariables",
      "disallowPackedArrays",
      "locationInfoStyle=wrapInAtSquareBracket"
    ).reduce(_ + "," + _)
  )
  circt.stage.ChiselStage.emitSystemVerilogFile(
    freechips.rocketchip.diplomacy.LazyModule(new soc.SoCTop).module,
    args,
    firtoolOptions
  )
}
