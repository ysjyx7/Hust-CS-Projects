`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/09/11 01:59:21
// Design Name: 
// Module Name: testPC
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module testPC();
    reg clk,halt,cs,pre,rst;
    wire [31:0]Q;
    wire [31:0]PC;
    wire [31:0]IR;
    reg [31:0]PChelp;
    assign PC=PChelp;
    always @(PC)
    begin
    PChelp<=PC;
    end    
    initial
    begin
    clk=0;
    halt=0;
    cs=0;
    pre=0;
    rst=0;
    PChelp=0;
    #5  PChelp<=4;
    end
    always
    begin
    #10 clk=~clk;
    end
    REGISTER_FLIP_FLOP_PC pc(clk,1'b1,PC,rst,1'b1,cs,pre,Q);
    ROM_ROM R(Q[11:2],IR);
endmodule
