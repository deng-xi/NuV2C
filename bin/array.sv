module array(clk, safety1);
	input clk; output safety1;
	wire safety1;
	reg [2:0] counter;
	reg [2:0] mem [7:0];
	assign safety1 = (counter > 3'd0);

	always @ (posedge clk) begin
		counter <= counter + 3'd1;
		mem[counter] <= counter;
	end
	assert property (! (counter > 3'd0) ||
		mem[counter - 3'd1] == counter - 3'd1) ;

endmodule
