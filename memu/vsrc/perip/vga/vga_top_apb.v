module vga_top_apb(
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

  output [7:0]  vga_r,
  output [7:0]  vga_g,
  output [7:0]  vga_b,
  output        vga_hsync,
  output        vga_vsync,
  output        vga_valid
);

  localparam H_VISIBLE = 640;
  localparam H_FRONT   = 16;
  localparam H_SYNC    = 96;
  localparam H_BACK    = 48;
  localparam H_TOTAL   = H_VISIBLE + H_FRONT + H_SYNC + H_BACK;
  localparam V_VISIBLE = 480;
  localparam V_FRONT   = 10;
  localparam V_SYNC    = 2;
  localparam V_BACK    = 33;
  localparam V_TOTAL   = V_VISIBLE + V_FRONT + V_SYNC + V_BACK;
  localparam FB_WORDS  = H_VISIBLE * V_VISIBLE;

  reg [31:0] framebuffer [0:FB_WORDS-1];
  reg [1:0] pixel_div;
  reg [9:0] h_count;
  reg [9:0] v_count;

  wire access = in_psel && in_penable;
  wire [18:0] cpu_index = in_paddr[20:2];
  wire cpu_in_range = cpu_index < FB_WORDS;
  wire visible = h_count < H_VISIBLE && v_count < V_VISIBLE;
  wire [18:0] display_index = v_count * H_VISIBLE + {9'b0, h_count};
  wire [31:0] pixel = visible ? framebuffer[display_index] : 32'b0;

  assign in_pready = 1'b1;
  assign in_pslverr = access && !cpu_in_range;
  assign in_prdata = cpu_in_range ? framebuffer[cpu_index] : 32'b0;

  assign vga_valid = visible;
  assign vga_hsync = !(h_count >= H_VISIBLE + H_FRONT &&
                       h_count < H_VISIBLE + H_FRONT + H_SYNC);
  assign vga_vsync = !(v_count >= V_VISIBLE + V_FRONT &&
                       v_count < V_VISIBLE + V_FRONT + V_SYNC);
  assign vga_r = visible ? pixel[23:16] : 8'b0;
  assign vga_g = visible ? pixel[15:8] : 8'b0;
  assign vga_b = visible ? pixel[7:0] : 8'b0;

  always @(posedge clock) begin
    if (reset) begin
      pixel_div <= 2'b0;
      h_count <= 10'b0;
      v_count <= 10'b0;
    end else begin
      // 100 MHz SoC clock / 4 = 25 MHz pixel clock.
      pixel_div <= pixel_div + 1'b1;
      if (pixel_div == 2'b11) begin
        if (h_count == H_TOTAL - 1) begin
          h_count <= 10'b0;
          if (v_count == V_TOTAL - 1)
            v_count <= 10'b0;
          else
            v_count <= v_count + 1'b1;
        end else begin
          h_count <= h_count + 1'b1;
        end
      end

      if (access && in_pwrite && cpu_in_range) begin
        if (in_pstrb[0]) framebuffer[cpu_index][7:0] <= in_pwdata[7:0];
        if (in_pstrb[1]) framebuffer[cpu_index][15:8] <= in_pwdata[15:8];
        if (in_pstrb[2]) framebuffer[cpu_index][23:16] <= in_pwdata[23:16];
        if (in_pstrb[3]) framebuffer[cpu_index][31:24] <= in_pwdata[31:24];
      end
    end
  end

endmodule
