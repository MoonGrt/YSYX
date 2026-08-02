module gpio_top_apb(
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

  output [15:0] gpio_out,
  input  [15:0] gpio_in,
  output [7:0]  gpio_seg_0,
  output [7:0]  gpio_seg_1,
  output [7:0]  gpio_seg_2,
  output [7:0]  gpio_seg_3,
  output [7:0]  gpio_seg_4,
  output [7:0]  gpio_seg_5,
  output [7:0]  gpio_seg_6,
  output [7:0]  gpio_seg_7
);

  reg [15:0] led_reg;
  reg [31:0] seg_reg;

  wire access = in_psel && in_penable;
  wire write_access = access && in_pwrite;
  wire [3:0] addr = in_paddr[3:0];

  assign in_pready = 1'b1;
  assign in_pslverr = 1'b0;
  assign gpio_out = led_reg;

  assign in_prdata = (addr == 4'h0) ? {16'b0, led_reg} :
                     (addr == 4'h4) ? {16'b0, gpio_in} :
                     (addr == 4'h8) ? seg_reg : 32'b0;

  function [7:0] decode_hex;
    input [3:0] value;
    begin
      // NVBoard's seven-segment pins are active low, ordered abcdefg.dp.
      case (value)
        4'h0: decode_hex = 8'b00000011;
        4'h1: decode_hex = 8'b10011111;
        4'h2: decode_hex = 8'b00100101;
        4'h3: decode_hex = 8'b00001101;
        4'h4: decode_hex = 8'b10011001;
        4'h5: decode_hex = 8'b01001001;
        4'h6: decode_hex = 8'b01000001;
        4'h7: decode_hex = 8'b00011111;
        4'h8: decode_hex = 8'b00000001;
        4'h9: decode_hex = 8'b00001001;
        4'ha: decode_hex = 8'b00010001;
        4'hb: decode_hex = 8'b11000001;
        4'hc: decode_hex = 8'b01100011;
        4'hd: decode_hex = 8'b10000101;
        4'he: decode_hex = 8'b01100001;
        default: decode_hex = 8'b01110001;
      endcase
    end
  endfunction

  assign gpio_seg_0 = decode_hex(seg_reg[3:0]);
  assign gpio_seg_1 = decode_hex(seg_reg[7:4]);
  assign gpio_seg_2 = decode_hex(seg_reg[11:8]);
  assign gpio_seg_3 = decode_hex(seg_reg[15:12]);
  assign gpio_seg_4 = decode_hex(seg_reg[19:16]);
  assign gpio_seg_5 = decode_hex(seg_reg[23:20]);
  assign gpio_seg_6 = decode_hex(seg_reg[27:24]);
  assign gpio_seg_7 = decode_hex(seg_reg[31:28]);

  always @(posedge clock) begin
    if (reset) begin
      led_reg <= 16'b0;
      seg_reg <= 32'b0;
    end else if (write_access) begin
      if (addr == 4'h0) begin
        if (in_pstrb[0]) led_reg[7:0] <= in_pwdata[7:0];
        if (in_pstrb[1]) led_reg[15:8] <= in_pwdata[15:8];
      end else if (addr == 4'h8) begin
        if (in_pstrb[0]) seg_reg[7:0] <= in_pwdata[7:0];
        if (in_pstrb[1]) seg_reg[15:8] <= in_pwdata[15:8];
        if (in_pstrb[2]) seg_reg[23:16] <= in_pwdata[23:16];
        if (in_pstrb[3]) seg_reg[31:24] <= in_pwdata[31:24];
      end
    end
  end

endmodule
