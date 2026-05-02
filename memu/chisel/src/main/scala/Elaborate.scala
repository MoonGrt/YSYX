// object MiniRVTOP extends App {
//   val firtoolOptions = Array(
//     "--lowering-options=" + List(
//       // make yosys happy
//       // see https://github.com/llvm/circt/blob/main/docs/VerilogGeneration.md
//       "disallowLocalVariables",
//       "disallowPackedArrays",
//       "locationInfoStyle=wrapInAtSquareBracket"
//     ).reduce(_ + "," + _)
//   )
//   circt.stage.ChiselStage.emitSystemVerilogFile(new riscv.mini.MiniRVTOP(), args, firtoolOptions)
// }

object Riscv32ETOP extends App {
  val firtoolOptions = Array(
    "--lowering-options=" + List(
      // make yosys happy
      // see https://github.com/llvm/circt/blob/main/docs/VerilogGeneration.md
      "disallowLocalVariables",
      "disallowPackedArrays",
      "locationInfoStyle=wrapInAtSquareBracket"
    ).reduce(_ + "," + _)
  )
  circt.stage.ChiselStage.emitSystemVerilogFile(new riscv.e.Riscv32ETOP, args, firtoolOptions)
}
