module top(clk,a);
input a,clk;
reg b,d;

wire a;

//assign statements updated in the same clock edge
wire c = b;

always @(posedge clk) begin
  b=a;
  d=c;
end

endmodule 
