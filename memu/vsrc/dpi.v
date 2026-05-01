import "DPI-C" function void exception(input byte code);
module Exception (
  input clk,
  input en,
  input [7:0] code
);
  always @(posedge clk) if (en) exception(code);
endmodule

import "DPI-C" function void dpi_diffpc(
  input int pc, input int npc, input int inst
);
module DiffPC (
  input [31:0] pc, npc, inst
);
  always @(*) dpi_diffpc(pc, npc, inst);
endmodule
import "DPI-C" function void dpi_diffgpr(input int gpr [0:31]);
module DiffGPR (
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
  always @(*) begin
    gpr[0]  = gpr_0;  gpr[1]  = gpr_1;  gpr[2]  = gpr_2;  gpr[3]  = gpr_3;
    gpr[4]  = gpr_4;  gpr[5]  = gpr_5;  gpr[6]  = gpr_6;  gpr[7]  = gpr_7;
    gpr[8]  = gpr_8;  gpr[9]  = gpr_9;  gpr[10] = gpr_10; gpr[11] = gpr_11;
    gpr[12] = gpr_12; gpr[13] = gpr_13; gpr[14] = gpr_14; gpr[15] = gpr_15;
    gpr[16] = gpr_16; gpr[17] = gpr_17; gpr[18] = gpr_18; gpr[19] = gpr_19;
    gpr[20] = gpr_20; gpr[21] = gpr_21; gpr[22] = gpr_22; gpr[23] = gpr_23;
    gpr[24] = gpr_24; gpr[25] = gpr_25; gpr[26] = gpr_26; gpr[27] = gpr_27;
    gpr[28] = gpr_28; gpr[29] = gpr_29; gpr[30] = gpr_30; gpr[31] = gpr_31;
  end
  always @(*) dpi_diffgpr(gpr);
endmodule

import "DPI-C" function void dpi_diffcsr(input int csr [0:7]);
module DiffCSR (
  input [31:0] csr_0, csr_1, csr_2, csr_3,
  input [31:0] csr_4, csr_5, csr_6, csr_7
);
  int csr [0:7];
  always @(*) begin
    csr[0] = csr_0; csr[1] = csr_1; csr[2] = csr_2; csr[3] = csr_3;
    csr[4] = csr_4; csr[5] = csr_5; csr[6] = csr_6; csr[7] = csr_7;
  end
  always @(*) dpi_diffcsr(csr);
endmodule



import "DPI-C" function int  dpi_paddr_read(input int addr);
import "DPI-C" function void dpi_paddr_write(input int addr, input byte mask, input int data);

module ROM_DPI(
  input  wire        clk,
  output wire        req_ready,
  input  wire [31:0] addr,
  input  wire        req_valid,
  input  wire        resp_ready,
  output reg  [31:0] data,
  output reg         resp_valid
);
  assign req_ready = 'b1;
  always @(posedge clk) data <= dpi_paddr_read(addr);
  always @(posedge clk) if (resp_ready) resp_valid <= req_valid;
endmodule
module RAM_DPI(
  input  wire        clk,
  output wire        req_ready,
  input  wire        ren,
  input  wire        wen,
  input  wire [ 7:0] mask,
  input  wire [31:0] addr,
  input  wire [31:0] wdata,
  input  wire        req_valid,
  input  wire        resp_ready,
  output reg  [31:0] rdata,
  output reg         resp_valid
);
  assign req_ready = 'b1;
  always @(posedge clk) begin
    rdata <= ren ? dpi_paddr_read(addr) : 'b0;
    if (req_valid && wen) dpi_paddr_write(addr, mask, wdata);
    if (resp_ready) resp_valid <= req_valid;
  end
endmodule
