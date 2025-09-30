module Dual_Control_Switch(
  input a,
  input b,
  output f
);
  assign f = a ^ b;
endmodule
