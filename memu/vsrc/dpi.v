`define CORE_RVMINI
`define CORE_RVE

// Mem
import "DPI-C" function int  dpi_paddr_read(input int addr);
import "DPI-C" function void dpi_paddr_write(input int addr, input byte mask, input int data);
module DpiMem(
    input  wire        ren,
    input  wire        wen,
    input  wire [ 7:0] mask,
    input  wire [31:0] addr,
    input  wire [31:0] wdata,
    output reg  [31:0] rdata
);
  always @(ren, wen, addr) begin
    rdata = 0;
    if (ren) rdata = dpi_paddr_read(addr);
    if (wen) dpi_paddr_write(addr, mask, wdata);
  end
endmodule

// Exception
import "DPI-C" function void exception(input byte code);
module DpiExceptionBB (
  input clk,
  input en,
  input [7:0] code
);
  always @(posedge clk) if (en) exception(code);
endmodule

// DiffTest
import "DPI-C" function void dpi_diffpc(input int pc, input int npc, input int inst);
import "DPI-C" function void dpi_diffgpr(input int gpr [0:15]);
import "DPI-C" function void dpi_diffcsr(input int csr [0:7]);
module DpiDiffPCBB (
  input clk, en,
  input [31:0] pc, npc, inst
);
  always @(posedge clk) if (en) dpi_diffpc(pc, npc, inst);
endmodule
module DpiDiffGPRBB (
  input [31:0] gpr_0,  gpr_1,  gpr_2,  gpr_3,
  input [31:0] gpr_4,  gpr_5,  gpr_6,  gpr_7,
  input [31:0] gpr_8,  gpr_9,  gpr_10, gpr_11,
  input [31:0] gpr_12, gpr_13, gpr_14, gpr_15
);
  int gpr [0:15];
  always @(*) begin
    gpr[0]  = gpr_0;  gpr[1]  = gpr_1;  gpr[2]  = gpr_2;  gpr[3]  = gpr_3;
    gpr[4]  = gpr_4;  gpr[5]  = gpr_5;  gpr[6]  = gpr_6;  gpr[7]  = gpr_7;
    gpr[8]  = gpr_8;  gpr[9]  = gpr_9;  gpr[10] = gpr_10; gpr[11] = gpr_11;
    gpr[12] = gpr_12; gpr[13] = gpr_13; gpr[14] = gpr_14; gpr[15] = gpr_15;
  end
  always @(*) dpi_diffgpr(gpr);
endmodule
module DpiDiffCSRBB (
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

// UART
import "DPI-C" function void difftest_skip_ref();
module UART(
  input en,
  input [7:0] data
);
  always @(*) 
    if (en) begin
      $write("%c",data);
      difftest_skip_ref();
    end
endmodule
