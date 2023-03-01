// This module tests the following:
// 1> passing module parameter list with input, output parameters

// 2> continuous assignments of type "wire [7:0] tmp = out;" and bit-wise extraction operator like "wire [3:0] st = out[7:4];"
// 3> output register
// 4> For non-blocking assignment, not only save the original assignments but also save the entire block of if-else, for etc. 
// 5> For output reg type variable, update both structure variable for local copy as well as the output pointer variable (so duplicate the statement here). Note that all the decision based on output variable will be based on pointer passed as reference and not on the local structure copy. Only the local structure copy is updated for any assignment statements. 
// 6> For only output type variable, update the output pointer variable only.Eg, Convert "assign dout = sr;" into
//    "*dout = sr; where dout is output variable."

//module up_counter(output [7:0] out, output [7:0] dout, input enable, input clk, input reset);
// Support statements like "parameter [1:0] idle = 2'b00;"
// Support statements like "if(|tmp[5:2])"

module top(out, dout, enable, clk, reset, o1);
output [7:0] out, dout;
output o1;
input enable, clk, reset;
reg [7:0] out;
reg x;
wire [7:0] dout;
wire [7:0] tmp;
//wire [7:0] tmp1 = out;
//wire [3:0] st = out[7:4];
assign tmp = out;
assign dout = out;
assign o1 = out;
always @(posedge clk)
if (reset) begin
  out <= 8'b0 ;
	x <= 1'b1;
end else if (enable) begin
  out <= out + 1;
	x <= 1'b0;
end
always @(posedge clk)
if (reset) begin
  out <= 8'b1 ;
	x <= 1'b0;
end else if (enable) begin
  out <= out - 1;
	x <= 1'b1;
end
endmodule 
