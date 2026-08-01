module psram(
  input sck,
  input ce_n,
  inout [3:0] dio
);

  localparam MEM_SIZE = 4 * 1024 * 1024;
  localparam CMD_READ  = 8'heb;
  localparam CMD_WRITE = 8'h38;
  localparam CMD_QPI   = 8'h35;

  reg [7:0] mem [0:MEM_SIZE-1];
  reg [7:0] command;
  reg [23:0] address;
  reg [7:0] phase;
  reg [3:0] read_data;
  reg read_enable;
  reg qpi_mode = 1'b0;

  wire [3:0] dio_in = dio;
  wire [23:0] byte_address = address & (MEM_SIZE - 1);
  wire [23:0] write_offset = ({16'd0, phase} - 24'd8) >> 1;
  wire [23:0] read_offset  = ({16'd0, phase} - 24'd15) >> 1;

  assign dio = read_enable ? read_data : 4'bz;

  always @(posedge sck or posedge ce_n) begin
    if (ce_n) begin
      if (!qpi_mode && command == CMD_QPI)
        qpi_mode <= 1'b1;
      command <= 8'd0;
      address <= 24'd0;
      phase   <= 8'd0;
    end
    else begin
      if ((!qpi_mode && phase < 8) || (qpi_mode && phase < 2))
        command <= qpi_mode ? {command[3:0], dio_in} :
                              {command[6:0], dio_in[0]};
      else if (qpi_mode && phase >= 2 && phase < 8)
        address <= {address[19:0], dio_in};
      else if (command == CMD_WRITE) begin
        if (!phase[0])
          mem[(byte_address + write_offset) & (MEM_SIZE - 1)][7:4]
            <= dio_in;
        else
          mem[(byte_address + write_offset) & (MEM_SIZE - 1)][3:0]
            <= dio_in;
      end
      phase <= phase + 1'b1;
    end
  end

  always @(*) begin
    read_enable = !ce_n && qpi_mode && command == CMD_READ && phase >= 15;
    read_data = 4'd0;
    if (read_enable) begin
      if (phase[0])
        read_data =
          mem[(byte_address + read_offset) & (MEM_SIZE - 1)][7:4];
      else
        read_data =
          mem[(byte_address + read_offset) & (MEM_SIZE - 1)][3:0];
    end
  end

endmodule
