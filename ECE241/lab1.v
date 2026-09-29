module swToLed (SW, LEDR);
input [9:0] SW; // toggle switches
output [9:0] LEDR; // LEDs
assign LEDR = SW;
endmodule

module mux2to1(x,y,s,f);
    input x,y,s;
    output f;

    assign f=(~s&x)|(s&y);
endmodule


module mux4bit2to1 (x,y,s,f);
    input [3:0] x,y;
    input s;
    output [3:0] f;

    mux2to1 mux1 (.x(x[0]),.y(y[0]),.s(s),.f(f[0]));
    mux2to1 mux2 (.x(x[1]),.y(y[1]),.s(s),.f(f[1]));
    mux2to1 mux3 (.x(x[2]),.y(y[2]),.s(s),.f(f[2]));
    mux2to1 mux4 (.x(x[3]),.y(y[3]),.s(s),.f(f[3]));
endmodule

module mux3to1(u,v,w,s,f);
    input u,v,w;
    input [1:0] s;
    output f;

    wire mux1_out; //add wire so they can connect

    mux2to1 mux1 (.x(u),.y(v),.s(s[0]),.f(mux1_out));//实列名称mux1
    mux2to1 mux2 (.x(mux1_out),.y(w),.s(s[1]),.f(f));
endmodule

module mux2bit3to1 (u,v,w,s,f);
    input [1:0] u,v,w;
    input [1:0] s;
    output [1:0] f;

    mux3to1 mux1 (.u(u[0]),.v(v[0]),.w(w[0]),.s(s),.f(f[0]));
    mux3to1 mux2 (.u(u[1]),.v(v[1]),.w(w[1]),.s(s),.f(f[1]));
endmodule

module dE1_displayer (C,HEX);
    input [1:0] C;
    output [6:0] HEX;

    wire [6:0] SW;

    assign HEX[0] = C[1] | ~C[0];
    assign HEX[1] = C[0];
    assign HEX[2] = C[0];
    assign HEX[3] = C[1];
    assign HEX[4] = C[1];
    assign HEX[5] = C[1] | ~C[0];
    assign HEX[6] = C[1];
    assign HEX=SW;
    
endmodule