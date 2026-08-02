module ps2_top_apb(
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

  input         ps2_clk,
  input         ps2_data
);

  // A host key event produces a make code and a two-byte break sequence.
  // Keep enough entries for a short burst while software is not polling.
  localparam FIFO_DEPTH = 32;
  reg [7:0] fifo [0:FIFO_DEPTH-1];
  reg [4:0] read_ptr;
  reg [4:0] write_ptr;
  reg [5:0] fifo_count;

  reg [2:0] ps2_clk_sync;
  reg [10:0] frame;
  reg [3:0] bit_count;

  wire falling_edge = ps2_clk_sync[2] && !ps2_clk_sync[1];
  wire data_register = in_paddr[2:0] == 3'b000;
  wire read_access = in_psel && in_penable && !in_pwrite && data_register;
  wire frame_valid = frame[0] == 1'b0 &&
                     ps2_data == 1'b1 &&
                     ^frame[9:1];
  wire push = falling_edge && bit_count == 4'd10 && frame_valid &&
              fifo_count != FIFO_DEPTH;
  wire pop = read_access && fifo_count != 0;

  assign in_pready = 1'b1;
  assign in_pslverr = 1'b0;
  assign in_prdata = !data_register || fifo_count == 0 ?
                     32'b0 : {24'b0, fifo[read_ptr]};

  always @(posedge clock) begin
    if (reset) begin
      ps2_clk_sync <= 3'b111;
      frame <= 11'b0;
      bit_count <= 4'b0;
      read_ptr <= 5'b0;
      write_ptr <= 5'b0;
      fifo_count <= 6'b0;
    end else begin
      ps2_clk_sync <= {ps2_clk_sync[1:0], ps2_clk};

      if (falling_edge) begin
        // Ignore idle clock edges until a valid low start bit arrives.
        // NVBoard may toggle the clock once before driving the first start
        // bit; counting that edge shifts every following PS/2 frame.
        if (bit_count == 4'd0) begin
          if (!ps2_data) begin
            frame[0] <= 1'b0;
            bit_count <= 4'd1;
          end
        end else begin
          frame[bit_count] <= ps2_data;
          if (bit_count == 4'd10)
            bit_count <= 4'b0;
          else
            bit_count <= bit_count + 1'b1;
        end
      end

      if (push) begin
        fifo[write_ptr] <= frame[8:1];
        write_ptr <= write_ptr + 1'b1;
      end
      if (pop)
        read_ptr <= read_ptr + 1'b1;

      case ({push, pop})
        2'b10: fifo_count <= fifo_count + 1'b1;
        2'b01: fifo_count <= fifo_count - 1'b1;
        default: fifo_count <= fifo_count;
      endcase
    end
  end

endmodule
