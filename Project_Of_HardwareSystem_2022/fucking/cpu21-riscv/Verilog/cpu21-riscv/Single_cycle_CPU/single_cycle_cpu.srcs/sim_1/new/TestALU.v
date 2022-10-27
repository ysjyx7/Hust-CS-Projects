`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/09/12 13:37:40
// Design Name: 
// Module Name: TestALU
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


module TestALU();
    wire [31:0]RDin,Result;
    wire less,equal,nol;
    ALU ALU1(6,32'h5,32'h1,less,equal,Result,RDin,nol);
endmodule
