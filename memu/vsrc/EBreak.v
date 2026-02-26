import "DPI-C" function void ebreak(input byte code);

module EBreak (
  input clk,
  input trap,
  input [7:0] code
);
  always @(posedge clk) if (trap) ebreak(code);
endmodule
