module sdram_top_axi(
  input         clock,
  input         reset,
  output        in_awready,
  input         in_awvalid,
  input  [31:0] in_awaddr,
  input  [3:0]  in_awid,
  input  [7:0]  in_awlen,
  input  [2:0]  in_awsize,
  input  [1:0]  in_awburst,
  input         in_awlock,
  input  [3:0]  in_awcache,
  input  [2:0]  in_awprot,
  input  [3:0]  in_awqos,
  output        in_wready,
  input         in_wvalid,
  input  [31:0] in_wdata,
  input  [3:0]  in_wstrb,
  input         in_wlast,
  input         in_bready,
  output        in_bvalid,
  output [1:0]  in_bresp,
  output [3:0]  in_bid,
  output        in_arready,
  input         in_arvalid,
  input  [31:0] in_araddr,
  input  [3:0]  in_arid,
  input  [7:0]  in_arlen,
  input  [2:0]  in_arsize,
  input  [1:0]  in_arburst,
  input         in_arlock,
  input  [3:0]  in_arcache,
  input  [2:0]  in_arprot,
  input  [3:0]  in_arqos,
  input         in_rready,
  output        in_rvalid,
  output [1:0]  in_rresp,
  output [31:0] in_rdata,
  output        in_rlast,
  output [3:0]  in_rid,

  output        sdram_clk,
  output        sdram_cke,
  output        sdram_cs,
  output        sdram_ras,
  output        sdram_cas,
  output        sdram_we,
  output [12:0] sdram_a,
  output [ 1:0] sdram_ba,
  output [ 3:0] sdram_dqm,
  inout  [31:0] sdram_dq
);

`ifdef FAST_SDRAM

  import "DPI-C" function int soc_sdram_read(input int addr);
  import "DPI-C" function void soc_sdram_write(
    input int addr, input byte mask, input int data
  );

  function [31:0] next_addr;
    input [31:0] addr;
    input [1:0] burst;
    input [7:0] len;
    input [2:0] size;
    reg [31:0] step;
    reg [31:0] mask;
    begin
      step = 32'b1 << size;
      mask = (({24'b0, len} + 32'b1) << size) - 32'b1;
      case (burst)
        2'b00: next_addr = addr;
        2'b10: next_addr = (addr & ~mask) | ((addr + step) & mask);
        default: next_addr = addr + step;
      endcase
    end
  endfunction

  reg        wr_active;
  reg [31:0] wr_addr;
  reg [3:0]  wr_id;
  reg [7:0]  wr_remaining;
  reg [7:0]  wr_len;
  reg [2:0]  wr_size;
  reg [1:0]  wr_burst;
  reg        b_valid;
  reg [3:0]  b_id;

  reg        rd_active;
  reg [31:0] rd_addr;
  reg [7:0]  rd_remaining;
  reg [7:0]  rd_len;
  reg [2:0]  rd_size;
  reg [1:0]  rd_burst;
  reg        r_valid;
  reg [31:0] r_data;
  reg [3:0]  r_id;
  reg        r_last;

  assign in_awready = !wr_active && !b_valid;
  assign in_wready  = wr_active && !b_valid;
  assign in_bvalid  = b_valid;
  assign in_bresp   = 2'b00;
  assign in_bid     = b_id;

  assign in_arready = !rd_active && !r_valid;
  assign in_rvalid  = r_valid;
  assign in_rresp   = 2'b00;
  assign in_rdata   = r_data;
  assign in_rlast   = r_last;
  assign in_rid     = r_id;

  // The functional model bypasses the SDRAM particles. Keep their pins idle
  // so the fast path cannot accidentally issue pin-level commands.
  assign sdram_clk = clock;
  assign sdram_cke = 1'b0;
  assign sdram_cs  = 1'b1;
  assign sdram_ras = 1'b1;
  assign sdram_cas = 1'b1;
  assign sdram_we  = 1'b1;
  assign sdram_a   = 13'b0;
  assign sdram_ba  = 2'b0;
  assign sdram_dqm = 4'hf;
  assign sdram_dq  = 32'bz;

  always @(posedge clock) begin
    if (reset) begin
      wr_active    <= 1'b0;
      wr_addr      <= 32'b0;
      wr_id        <= {4{1'b0}};
      wr_remaining <= 8'b0;
      wr_len       <= 8'b0;
      wr_size      <= 3'b0;
      wr_burst     <= 2'b0;
      b_valid      <= 1'b0;
      b_id         <= {4{1'b0}};
      rd_active    <= 1'b0;
      rd_addr      <= 32'b0;
      rd_remaining <= 8'b0;
      rd_len       <= 8'b0;
      rd_size      <= 3'b0;
      rd_burst     <= 2'b0;
      r_valid      <= 1'b0;
      r_data       <= 32'b0;
      r_id         <= {4{1'b0}};
      r_last       <= 1'b0;
    end else begin
      if (in_awvalid && in_awready) begin
        wr_active    <= 1'b1;
        wr_addr      <= in_awaddr;
        wr_id        <= in_awid;
        wr_remaining <= in_awlen;
        wr_len       <= in_awlen;
        wr_size      <= in_awsize;
        wr_burst     <= in_awburst;
      end
      if (in_wvalid && in_wready) begin
        soc_sdram_write(wr_addr, {4'b0, in_wstrb}, in_wdata);
        if (wr_remaining == 0) begin
          wr_active <= 1'b0;
          b_valid   <= 1'b1;
          b_id      <= wr_id;
        end else begin
          wr_addr      <= next_addr(wr_addr, wr_burst, wr_len, wr_size);
          wr_remaining <= wr_remaining - 1'b1;
        end
      end else if (b_valid && in_bready) begin
        b_valid <= 1'b0;
      end

      if (in_arvalid && in_arready) begin
        rd_active    <= 1'b1;
        rd_addr      <= in_araddr;
        rd_remaining <= in_arlen;
        rd_len       <= in_arlen;
        rd_size      <= in_arsize;
        rd_burst     <= in_arburst;
        r_data       <= soc_sdram_read(in_araddr);
        r_id         <= in_arid;
        r_last       <= in_arlen == 0;
        r_valid      <= 1'b1;
      end else if (r_valid && in_rready) begin
        if (rd_remaining == 0) begin
          rd_active <= 1'b0;
          r_valid   <= 1'b0;
          r_last    <= 1'b0;
        end else begin
          rd_addr      <= next_addr(rd_addr, rd_burst, rd_len, rd_size);
          rd_remaining <= rd_remaining - 1'b1;
          r_data       <= soc_sdram_read(next_addr(rd_addr, rd_burst, rd_len, rd_size));
          r_last       <= rd_remaining == 1;
        end
      end
    end
  end

`else

  wire sdram_dout_en;
  wire [31:0] sdram_dout;
  assign sdram_dq = sdram_dout_en ? sdram_dout : 32'bz;
  sdram_axi #(
    .SDRAM_MHZ(100),
    .SDRAM_ADDR_W(24),
    .SDRAM_COL_W(9),
    .SDRAM_READ_LATENCY(2)
  ) u_sdram_axi(
    .clk_i(clock),
    .rst_i(reset),
    .inport_awvalid_i(in_awvalid),
    .inport_awaddr_i(in_awaddr),
    .inport_awid_i(in_awid),
    .inport_awlen_i(in_awlen),
    .inport_awburst_i(in_awburst),
    .inport_wvalid_i(in_wvalid),
    .inport_wdata_i(in_wdata),
    .inport_wstrb_i(in_wstrb),
    .inport_wlast_i(in_wlast),
    .inport_bready_i(in_bready),
    .inport_arvalid_i(in_arvalid),
    .inport_araddr_i(in_araddr),
    .inport_arid_i(in_arid),
    .inport_arlen_i(in_arlen),
    .inport_arburst_i(in_arburst),
    .inport_rready_i(in_rready),

    .inport_awready_o(in_awready),
    .inport_wready_o(in_wready),
    .inport_bvalid_o(in_bvalid),
    .inport_bresp_o(in_bresp),
    .inport_bid_o(in_bid),
    .inport_arready_o(in_arready),
    .inport_rvalid_o(in_rvalid),
    .inport_rdata_o(in_rdata),
    .inport_rresp_o(in_rresp),
    .inport_rid_o(in_rid),
    .inport_rlast_o(in_rlast),
    .sdram_clk_o(sdram_clk),
    .sdram_cke_o(sdram_cke),
    .sdram_cs_o(sdram_cs),
    .sdram_ras_o(sdram_ras),
    .sdram_cas_o(sdram_cas),
    .sdram_we_o(sdram_we),
    .sdram_dqm_o(sdram_dqm),
    .sdram_addr_o(sdram_a),
    .sdram_ba_o(sdram_ba),
    .sdram_data_input_i(sdram_dq),
    .sdram_data_output_o(sdram_dout),
    .sdram_data_out_en_o(sdram_dout_en)
  );

`endif

endmodule
