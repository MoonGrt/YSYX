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

import "DPI-C" function void diff(
  input int pc, input int npc, input int inst,
  input int gpr [0:31], input int csr [0:3]
);
module DiffTest (
  input clk,
  input [31:0] pc, npc, inst,
  input [31:0] csr_0,  csr_1,  csr_2,  csr_3,
  input [31:0] gpr_0,  gpr_1,  gpr_2,  gpr_3,
  input [31:0] gpr_4,  gpr_5,  gpr_6,  gpr_7,
  input [31:0] gpr_8,  gpr_9,  gpr_10, gpr_11,
  input [31:0] gpr_12, gpr_13, gpr_14, gpr_15,
  input [31:0] gpr_16, gpr_17, gpr_18, gpr_19,
  input [31:0] gpr_20, gpr_21, gpr_22, gpr_23,
  input [31:0] gpr_24, gpr_25, gpr_26, gpr_27,
  input [31:0] gpr_28, gpr_29, gpr_30, gpr_31
);
  int gpr [0:31];
  int csr [0:3];
  always @(*) begin
    csr[0]  = csr_0;  csr[1]  = csr_1;  csr[2]  = csr_2;  csr[3]  = csr_3;
    gpr[0]  = gpr_0;  gpr[1]  = gpr_1;  gpr[2]  = gpr_2;  gpr[3]  = gpr_3;
    gpr[4]  = gpr_4;  gpr[5]  = gpr_5;  gpr[6]  = gpr_6;  gpr[7]  = gpr_7;
    gpr[8]  = gpr_8;  gpr[9]  = gpr_9;  gpr[10] = gpr_10; gpr[11] = gpr_11;
    gpr[12] = gpr_12; gpr[13] = gpr_13; gpr[14] = gpr_14; gpr[15] = gpr_15;
    gpr[16] = gpr_16; gpr[17] = gpr_17; gpr[18] = gpr_18; gpr[19] = gpr_19;
    gpr[20] = gpr_20; gpr[21] = gpr_21; gpr[22] = gpr_22; gpr[23] = gpr_23;
    gpr[24] = gpr_24; gpr[25] = gpr_25; gpr[26] = gpr_26; gpr[27] = gpr_27;
    gpr[28] = gpr_28; gpr[29] = gpr_29; gpr[30] = gpr_30; gpr[31] = gpr_31;
  end
  always @(*) diff(pc, npc, inst, gpr, csr);
endmodule







module ROM_DPI(
  input  wire [31:0] addr,
  output wire [31:0] data
);
  // always @(*) data = pmem_read(addr);
  assign data = pmem_read(addr);
endmodule

module RAM_DPI(
  input  wire        re,
  input  wire        we,
  input  wire [31:0] addr,
  input  wire [ 7:0] mask,
  input  wire [31:0] wdata,
  output reg  [31:0] rdata
);
  always @(*) begin
    rdata = 0;
    if (re) rdata = pmem_read(addr);
    if (we) pmem_write(addr, mask, wdata);
  end
endmodule
