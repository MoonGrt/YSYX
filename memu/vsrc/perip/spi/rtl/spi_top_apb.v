module spi_top_apb #(
  parameter flash_addr_start = 32'h30000000,
  parameter flash_addr_end   = 32'h3fffffff,
  parameter spi_ss_num       = 8
) (
  input         clock,
  input         reset,
  input  [31:0] in_paddr,
  input         in_psel,
  input         in_penable,
  input  [2:0]  in_pprot,
  input         in_pwrite,
  input  [31:0] in_pwdata,
  input  [3:0]  in_pstrb,
  output        in_pready,
  output [31:0] in_prdata,
  output        in_pslverr,

  output                  spi_sck,
  output [spi_ss_num-1:0] spi_ss,
  output                  spi_mosi,
  input                   spi_miso,
  output                  spi_irq_out
);

`ifdef FAST_FLASH

wire        is_xip = in_paddr >= flash_addr_start && in_paddr <= flash_addr_end;
wire [31:0] xip_data;
wire        wb_pready;
wire [31:0] wb_prdata;
wire        wb_pslverr;
wire        wb_irq;
wire        wb_sck;
wire [spi_ss_num-1:0] wb_ss;
wire        wb_mosi;

flash_cmd flash_cmd_i(
  .clock(clock),
  .valid(in_psel && !in_penable && is_xip && !in_pwrite),
  .cmd(8'h03),
  .addr({8'b0, in_paddr[23:2], 2'b0}),
  .data(xip_data)
);

spi_top u0_spi_top (
  .wb_clk_i(clock),
  .wb_rst_i(reset),
  .wb_adr_i(in_paddr[4:0]),
  .wb_dat_i(in_pwdata),
  .wb_dat_o(wb_prdata),
  .wb_sel_i(in_pstrb),
  .wb_we_i (in_pwrite),
  .wb_stb_i(in_psel && !is_xip),
  .wb_cyc_i(in_penable && !is_xip),
  .wb_ack_o(wb_pready),
  .wb_err_o(wb_pslverr),
  .wb_int_o(wb_irq),
  .ss_pad_o(wb_ss),
  .sclk_pad_o(wb_sck),
  .mosi_pad_o(wb_mosi),
  .miso_pad_i(spi_miso)
);

assign spi_sck     = wb_sck;
assign spi_ss      = wb_ss;
assign spi_mosi    = wb_mosi;
assign spi_irq_out = wb_irq;
assign in_pready   = is_xip ? in_penable && in_psel : wb_pready;
assign in_prdata   = is_xip ? xip_data : wb_prdata;
assign in_pslverr  = is_xip ? in_pwrite : wb_pslverr;

always @(posedge clock) begin
  if (in_psel && in_penable && is_xip && in_pwrite) begin
    $fwrite(32'h80000002, "Assertion failed: XIP flash is read-only\n");
    $fatal;
  end
end

`else

localparam XIP_IDLE = 4'd0;
localparam XIP_DIV  = 4'd1;
localparam XIP_SS   = 4'd2;
localparam XIP_TX0  = 4'd3;
localparam XIP_TX1  = 4'd4;
localparam XIP_CTRL = 4'd5;
localparam XIP_POLL = 4'd6;
localparam XIP_RX0  = 4'd7;
localparam XIP_RESP = 4'd8;

wire is_xip = in_paddr >= flash_addr_start && in_paddr <= flash_addr_end;
reg [3:0]  xip_state;
reg        xip_wb_active;
reg [23:0] xip_addr;
reg [31:0] xip_data;

wire        xip_busy = xip_state != XIP_IDLE;
wire [4:0]  xip_wb_addr =
  xip_state == XIP_DIV  ? 5'h14 :
  xip_state == XIP_SS   ? 5'h18 :
  xip_state == XIP_TX0  ? 5'h00 :
  xip_state == XIP_TX1  ? 5'h04 :
  xip_state == XIP_CTRL ? 5'h10 :
  xip_state == XIP_POLL ? 5'h10 : 5'h00;
wire [31:0] xip_wb_data =
  xip_state == XIP_SS   ? 32'h00000001 :
  xip_state == XIP_TX1  ? {8'h03, xip_addr} :
  xip_state == XIP_CTRL ? 32'h00002540 : 32'h00000000;
wire xip_wb_write = xip_state >= XIP_DIV && xip_state <= XIP_CTRL;

wire        wb_pready;
wire [31:0] wb_prdata;
wire        wb_pslverr;
wire        wb_irq;

spi_top u0_spi_top (
  .wb_clk_i(clock),
  .wb_rst_i(reset),
  .wb_adr_i(xip_busy ? xip_wb_addr : in_paddr[4:0]),
  .wb_dat_i(xip_busy ? xip_wb_data : in_pwdata),
  .wb_dat_o(wb_prdata),
  .wb_sel_i(xip_busy ? 4'hf : in_pstrb),
  .wb_we_i (xip_busy ? xip_wb_write : in_pwrite),
  .wb_stb_i(xip_busy ? xip_wb_active : in_psel && !is_xip),
  .wb_cyc_i(xip_busy ? xip_wb_active : in_penable && !is_xip),
  .wb_ack_o(wb_pready),
  .wb_err_o(wb_pslverr),
  .wb_int_o(wb_irq),

  .ss_pad_o(spi_ss),
  .sclk_pad_o(spi_sck),
  .mosi_pad_o(spi_mosi),
  .miso_pad_i(spi_miso)
);

assign in_pready   = (is_xip || xip_busy) ?
                     (xip_state == XIP_RESP && in_penable) : wb_pready;
assign in_prdata   = (is_xip || xip_busy) ? xip_data : wb_prdata;
assign in_pslverr  = (is_xip || xip_busy) ? in_pwrite : wb_pslverr;
assign spi_irq_out = wb_irq;

always @(posedge clock) begin
  if (reset) begin
    xip_state     <= XIP_IDLE;
    xip_wb_active <= 1'b0;
    xip_addr      <= 24'b0;
    xip_data      <= 32'b0;
  end else begin
    if (xip_state == XIP_IDLE) begin
      xip_wb_active <= 1'b0;
      if (in_psel && !in_penable && is_xip && !in_pwrite) begin
        xip_addr  <= {in_paddr[23:2], 2'b0};
        xip_state <= XIP_DIV;
      end
    end else if (xip_state == XIP_RESP) begin
      if (in_psel && in_penable) xip_state <= XIP_IDLE;
    end else if (!xip_wb_active) begin
      // Leave one idle Wishbone cycle between register accesses so that the
      // SPI core can lower wb_ack_o before the next transaction.
      xip_wb_active <= 1'b1;
    end else if (wb_pready) begin
      xip_wb_active <= 1'b0;
      case (xip_state)
        XIP_DIV:  xip_state <= XIP_SS;
        XIP_SS:   xip_state <= XIP_TX0;
        XIP_TX0:  xip_state <= XIP_TX1;
        XIP_TX1:  xip_state <= XIP_CTRL;
        XIP_CTRL: xip_state <= XIP_POLL;
        XIP_POLL: if (!wb_prdata[8]) xip_state <= XIP_RX0;
        XIP_RX0: begin
          xip_data  <= {wb_prdata[7:0], wb_prdata[15:8],
                        wb_prdata[23:16], wb_prdata[31:24]};
          xip_state <= XIP_RESP;
        end
        default: xip_state <= XIP_IDLE;
      endcase
    end
  end
end

always @(posedge clock) begin
  if (in_psel && in_penable && is_xip && in_pwrite) begin
    $fwrite(32'h80000002, "Assertion failed: XIP flash is read-only\n");
    $fatal;
  end
end

`endif // FAST_FLASH

endmodule
