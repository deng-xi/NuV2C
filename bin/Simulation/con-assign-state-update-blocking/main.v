module top(clk,b);
input b,clk;
reg d;

//assign statements updated in the same clock edge
wire c = b;

always @(posedge clk) begin
  d=c;
end

endmodule 
