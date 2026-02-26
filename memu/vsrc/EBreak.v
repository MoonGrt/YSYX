import "DPI-C" function void ebreak(input byte code);

module EBreak (
  input trap,
  input [7:0] code
);
  always @* if (trap) ebreak(code);
endmodule
