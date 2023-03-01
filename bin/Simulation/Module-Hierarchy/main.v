// Module to test 3 level module hierarchy
module top(a,b,c);
	output [2:0] a;
	reg [2:0] a;
	input [2:0] b;
	input [2:0] c; 
  reg [0:2] x;
  wire [0:2] y; 

  B b1(x,y);

  always@(b or c or y) begin
	  if(b==3'b000) begin 
      x = c << 1;
    end 
    else begin
      a = y & b;
    end
  end
endmodule

module B(x,y);
	input [2:0] x;
	output [2:0] y;
	reg [2:0] y;
  wire [2:0] m;

  C c1(x,m);
  always@(x or m) begin
    if(x==3'b100) begin
      y = x + 1;
    end
    else begin
      y=0;
    end
  end
endmodule

module C(x,m);
  input [2:0] x;
  output [2:0] m;
  reg [2:0] m;
  always@(x) begin
    if(x==3'b100) begin
      m = x + 1;
    end
    else begin
      m=0;
    end
  end
endmodule

