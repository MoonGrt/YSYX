import "DPI-C" function void ebreak(input byte code);

module EBreak (
  input clk,
  input trap,
  input [7:0] code
);
  always @(posedge clk) if (trap) ebreak(code);
endmodule

import "DPI-C" function int  pmem_read(input int raddr);
import "DPI-C" function void pmem_write(input int waddr, input byte wmask, input int wdata);
module PMem(
  input valid,
  input [31:0] raddr,
  input [31:0] waddr,
  input [31:0] wdata,
  input [7:0] wmask,
  input wen,
  output reg [31:0] rdata
);
  always @(*) begin
    if (valid) begin
      rdata = pmem_read(raddr);
      if (wen) pmem_write(waddr, wdata, wmask);
    end else rdata = 0;
  end
endmodule

// import "DPI-C" function void diff(
//   input int pc, input int snpc, input int dnpc, input int inst,
//   input int regs_0,  input int regs_1,  input int regs_2,  input int regs_3,
//   input int regs_4,  input int regs_5,  input int regs_6,  input int regs_7,
//   input int regs_8,  input int regs_9,  input int regs_10, input int regs_11,
//   input int regs_12, input int regs_13, input int regs_14, input int regs_15,
//   input int regs_16, input int regs_17, input int regs_18, input int regs_19,
//   input int regs_20, input int regs_21, input int regs_22, input int regs_23,
//   input int regs_24, input int regs_25, input int regs_26, input int regs_27,
//   input int regs_28, input int regs_29, input int regs_30, input int regs_31
// );












module ROM_DPI(
  input  wire [31:0] addr,
  output wire [31:0] data
);
  // always @(*) data = pmem_read(addr);
  assign data = pmem_read(addr);
endmodule

module RAM_DPI(
  input  wire        we,
  input  wire [31:0] addr,
  input  wire [ 7:0] mask,
  input  wire [31:0] wdata,
  output reg  [31:0] rdata
);
  always @(*) begin
    rdata = pmem_read(addr);
    if (we) pmem_write(addr, mask, wdata);
  end
endmodule
