module top(out, enable ,clk, reset);
output [7:0] out;
input enable, clk, reset;
reg [7:0] out;
always @(posedge clk)
if (reset) begin
  out <= 8'b10111010 ;
  out[2] = 1'b1;
end else if (enable) begin
  out <= out + 1;
end
endmodule 
