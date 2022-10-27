`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/09/11 08:58:36
// Design Name: 
// Module Name: Testdisplay
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


module Testdisplay();
reg clk;
    wire [7:0]SEG,AN;
    reg [31:0]leddata;
    wire [2:0]flag;
    wire [3:0]y;
    initial
    begin
    leddata=0;
    clk=0;
    end
    always 
    begin
    #20 leddata=leddata+1;
    end
    always
    begin 
        #10 clk=~clk;
    end
    display dis(clk,leddata,AN,SEG,flag,y);
endmodule
