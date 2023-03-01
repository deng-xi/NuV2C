module A(x,foo,bar,y);
 input x,bar;
 output y,foo;

 assign foo=x;
 assign y=bar;

endmodule

/*
module B(input foo, output bar);
//input foo;
//output bar;
assign bar=foo;
endmodule
*/

module B(foo,bar);
input foo;
output bar;
assign bar=foo;
endmodule

module top();
 wire x,y,foo,bar;
 A a(x,foo,bar,y);
 //A a1(x,foo,bar,y);
 B b(foo,bar);
 assert property1: (x==y) && (y==foo) && (foo==bar);
endmodule
