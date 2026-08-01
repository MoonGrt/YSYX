module sdram(
  input        clk,
  input        cke,
  input        cs,
  input        ras,
  input        cas,
  input        we,
  input [12:0] a,
  input [ 1:0] ba,
  input [ 3:0] dqm,
  inout [31:0] dq
);

  // Two x16 particles share command/address lines and form one x32 word.
  sdram_x16 low_particle (
    .clk(clk), .cke(cke), .cs(cs), .ras(ras), .cas(cas), .we(we),
    .a(a), .ba(ba), .dqm(dqm[1:0]), .dq(dq[15:0])
  );

  sdram_x16 high_particle (
    .clk(clk), .cke(cke), .cs(cs), .ras(ras), .cas(cas), .we(we),
    .a(a), .ba(ba), .dqm(dqm[3:2]), .dq(dq[31:16])
  );

endmodule

module sdram_x16(
  input        clk,
  input        cke,
  input        cs,
  input        ras,
  input        cas,
  input        we,
  input [12:0] a,
  input [ 1:0] ba,
  input [ 1:0] dqm,
  inout [15:0] dq
);

  localparam HALF_WORDS    = 1 << 24;
  localparam CMD_ACTIVE    = 4'b0011;
  localparam CMD_READ      = 4'b0101;
  localparam CMD_WRITE     = 4'b0100;
  localparam CMD_PRECHARGE = 4'b0010;
  localparam CMD_LOAD_MODE = 4'b0000;

  reg [15:0] mem [0:HALF_WORDS-1];
  reg [12:0] active_row [0:3];
  reg [3:0] row_open;
  reg [2:0] cas_latency;
  reg [2:0] burst_length;

  reg write_pending;
  reg [23:0] write_index;

  reg read_pending;
  reg [2:0] read_delay;
  reg read_beat;
  reg [23:0] read_index;

  wire [3:0] command = {cs, ras, cas, we};
  wire [23:0] selected_index = {active_row[ba], ba, a[8:0]};
  wire [15:0] dq_in = dq;
  wire [15:0] dq_out =
      mem[(read_index + (read_beat ? 24'd1 : 24'd0)) &
          (HALF_WORDS - 1)];
  wire dq_enable = read_pending && read_delay == 0;

  assign dq = dq_enable ? dq_out : 16'bz;

  integer i;
  initial begin
    row_open = 4'd0;
    cas_latency = 3'd2;
    burst_length = 3'd1;
    write_pending = 1'b0;
    read_pending = 1'b0;
    read_delay = 3'd0;
    read_beat = 1'b0;
    for (i = 0; i < 4; i = i + 1)
      active_row[i] = 13'd0;
  end

  always @(posedge clk) begin
    if (!cke) begin
      write_pending <= 1'b0;
      read_pending <= 1'b0;
      read_delay <= 3'd0;
      read_beat <= 1'b0;
    end
    else begin
      if (write_pending) begin
        if (!dqm[0])
          mem[(write_index + 1'b1) & (HALF_WORDS - 1)][7:0]
            <= dq_in[7:0];
        if (!dqm[1])
          mem[(write_index + 1'b1) & (HALF_WORDS - 1)][15:8]
            <= dq_in[15:8];
        write_pending <= 1'b0;
      end

      if (read_pending) begin
        if (read_delay != 0)
          read_delay <= read_delay - 1'b1;
        else if (burst_length <= 1) begin
          read_pending <= 1'b0;
          read_beat <= 1'b0;
        end
        else if (!read_beat)
          read_beat <= 1'b1;
        else begin
          read_pending <= 1'b0;
          read_beat <= 1'b0;
        end
      end

      case (command)
        CMD_ACTIVE: begin
          active_row[ba] <= a;
          row_open[ba] <= 1'b1;
        end
        CMD_READ: if (row_open[ba]) begin
          read_index <= selected_index;
          read_delay <= cas_latency > 1 ? cas_latency - 1 : 0;
          read_pending <= 1'b1;
          read_beat <= 1'b0;
        end
        CMD_WRITE: if (row_open[ba]) begin
          if (!dqm[0])
            mem[selected_index][7:0] <= dq_in[7:0];
          if (!dqm[1])
            mem[selected_index][15:8] <= dq_in[15:8];
          write_index <= selected_index;
          write_pending <= burst_length > 1;
        end
        CMD_PRECHARGE: begin
          if (a[10])
            row_open <= 4'd0;
          else
            row_open[ba] <= 1'b0;
        end
        CMD_LOAD_MODE: begin
          cas_latency <= a[6:4];
          case (a[2:0])
            3'b000: burst_length <= 1;
            3'b001: burst_length <= 2;
            3'b010: burst_length <= 4;
            default: burst_length <= 2;
          endcase
        end
        default: begin end
      endcase
    end
  end

endmodule
