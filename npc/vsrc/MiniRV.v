module ROM_DPI(
  input  wire [31:0] addr,
  output reg  [31:0] data
);
  always @(*) data = pmem_read(addr);
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
