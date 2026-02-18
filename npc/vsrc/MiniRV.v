import "DPI-C" function void rom_rdpi(input int addr, output int data);
import "DPI-C" function int  ram_rdpi(input int raddr);
import "DPI-C" function void ram_wdpi(input int waddr, input int wdata, input byte wmask);

module ROM_DPI(
  input  wire [31:0] addr,
  output reg  [31:0] data
);
  always @(*) data = ram_rdpi(addr);
endmodule

module RAM_DPI(
  input  wire        we,
  input  wire [31:0] addr,
  input  wire [ 7:0] mask,
  input  wire [31:0] wdata,
  output reg  [31:0] rdata
);
  always @(*) begin
    rdata = ram_rdpi(addr);
    if (we) ram_wdpi(addr, wdata, mask);
  end
endmodule
