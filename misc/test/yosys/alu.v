module alu #(parameter WIDTH = 4) (
  input  [WIDTH-1:0] a,
  input  [WIDTH-1:0] b,
  input  [2:0] op,
  output reg [WIDTH-1:0] y
);
wire [WIDTH-1:0] add_res = a + b;
wire [WIDTH-1:0] sub_res = a - b;
always @(*) begin
  case (op)
    3'b000: y = add_res;
    3'b001: y = sub_res;
    3'b010: y = a << b;
    3'b011: y = a >> b;
    3'b100: y = (a < b);
    default: y = 0;
  endcase
end
endmodule
