module count(clk, out);
	input clk; output out;
	wire [3:0]out;
	reg [3:0] count;
	assign out = count;
	always @ (posedge clk) begin
	    if (count == 7)
	        count <= 0;
	    else
		    count  <= count + 1;
	end
	assert property (out < 8) ;
endmodule
