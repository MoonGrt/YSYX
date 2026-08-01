`timescale 1ns/1ps

module sdram32_tb;
  reg         clock = 0;
  reg         reset = 1;
  reg  [31:0] paddr = 0;
  reg         psel = 0;
  reg         penable = 0;
  reg         pwrite = 0;
  reg  [31:0] pwdata = 0;
  reg  [ 3:0] pstrb = 0;
  wire        pready;
  wire [31:0] prdata;
  wire        pslverr;
  wire        sdram_clk;
  wire        sdram_cke;
  wire        sdram_cs;
  wire        sdram_ras;
  wire        sdram_cas;
  wire        sdram_we;
  wire [12:0] sdram_a;
  wire [ 1:0] sdram_ba;
  wire [ 3:0] sdram_dqm;
  wire [31:0] sdram_dq;

  integer write_commands = 0;
  integer read_commands = 0;

  always #5 clock = ~clock;
  always @(posedge sdram_clk) begin
    if ({sdram_cs, sdram_ras, sdram_cas, sdram_we} == 4'b0100)
      write_commands = write_commands + 1;
    if ({sdram_cs, sdram_ras, sdram_cas, sdram_we} == 4'b0101)
      read_commands = read_commands + 1;
  end

  sdram_top_apb dut (
    .clock(clock), .reset(reset),
    .in_paddr(paddr), .in_psel(psel), .in_penable(penable),
    .in_pprot(3'b0), .in_pwrite(pwrite), .in_pwdata(pwdata),
    .in_pstrb(pstrb), .in_pready(pready), .in_prdata(prdata),
    .in_pslverr(pslverr),
    .sdram_clk(sdram_clk), .sdram_cke(sdram_cke), .sdram_cs(sdram_cs),
    .sdram_ras(sdram_ras), .sdram_cas(sdram_cas), .sdram_we(sdram_we),
    .sdram_a(sdram_a), .sdram_ba(sdram_ba), .sdram_dqm(sdram_dqm),
    .sdram_dq(sdram_dq)
  );

  sdram particles (
    .clk(sdram_clk), .cke(sdram_cke), .cs(sdram_cs),
    .ras(sdram_ras), .cas(sdram_cas), .we(sdram_we),
    .a(sdram_a), .ba(sdram_ba), .dqm(sdram_dqm), .dq(sdram_dq)
  );

  task apb_write;
    input [31:0] address;
    input [31:0] data;
    input [ 3:0] strobe;
    begin
      @(negedge clock);
      paddr = address; pwdata = data; pstrb = strobe;
      pwrite = 1; psel = 1; penable = 0;
      @(negedge clock);
      penable = 1;
      while (!pready) @(negedge clock);
      psel = 0; penable = 0; pwrite = 0; pstrb = 0;
    end
  endtask

  task apb_read;
    input [31:0] address;
    output [31:0] data;
    begin
      @(negedge clock);
      paddr = address; pwrite = 0; psel = 1; penable = 0;
      @(negedge clock);
      penable = 1;
      while (!pready) @(negedge clock);
      data = prdata;
      psel = 0; penable = 0;
    end
  endtask

  reg [31:0] value;
  initial begin
    repeat (4) @(negedge clock);
    reset = 0;

    apb_write(32'ha0000000, 32'h89abcdef, 4'b1111);
    apb_read (32'ha0000000, value);
    if (value !== 32'h89abcdef)
      $fatal(1, "32-bit read mismatch: %08x", value);
    if (write_commands !== 1 || read_commands !== 1)
      $fatal(1, "expected one SDRAM command per transfer, writes=%0d reads=%0d",
             write_commands, read_commands);

    apb_write(32'ha0000000, 32'h11223344, 4'b0101);
    apb_read (32'ha0000000, value);
    if (value !== 32'h8922cd44)
      $fatal(1, "DQM byte mask mismatch: %08x", value);

    if (particles.low_particle.mem[0] !== 16'hcd44 ||
        particles.high_particle.mem[0] !== 16'h8922)
      $fatal(1, "two x16 particles did not receive their respective halves");

    $display("SDRAM x32 bit-extension test passed");
    $finish;
  end
endmodule
