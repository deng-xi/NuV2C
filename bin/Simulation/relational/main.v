module top(clk,a);
input a,clk;
reg [1:0] b; 
wire a;

always @(posedge clk) 
 begin
  b=a+1;
 end
 assert property: (a > 0);
endmodule


