module top(clk,b);
input b,clk;
reg d,e;

//assign statements updated in the same clock edge
wire c = b;

always @(posedge clk) begin
  d<=c;
  e<=d;
end

endmodule 
