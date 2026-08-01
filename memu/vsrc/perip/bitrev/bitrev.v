module bitrev (
  input  sck,
  input  ss,
  input  mosi,
  output miso
);
  reg [4:0] bit_count;
  reg [7:0] data;

  always @(negedge sck or posedge ss) begin
    if (ss) begin
      bit_count <= 5'd0;
      data      <= 8'd0;
    end
    else begin
      if (bit_count < 5'd8)
        data <= {data[6:0], mosi};
      if (bit_count < 5'd16)
        bit_count <= bit_count + 5'd1;
    end
  end

  assign miso = ss ? 1'b1 :
                (bit_count == 5'd7) ? mosi :
                (bit_count >= 5'd8 && bit_count < 5'd15) ?
                data[bit_count[2:0] - 3'd7] : 1'b1;
endmodule
