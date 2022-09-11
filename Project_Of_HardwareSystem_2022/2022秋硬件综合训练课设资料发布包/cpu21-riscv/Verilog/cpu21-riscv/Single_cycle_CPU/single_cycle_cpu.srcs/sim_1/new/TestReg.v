`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/09/11 08:20:27
// Design Name: 
// Module Name: TestReg
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


module TestReg();
 reg clk;
 reg [4:0]R1Ch,R2Ch,Wch;
 reg [31:0]RDin;
 wire [31:0]R1Data,MDin;
 reg RegWrite;
 initial 
 begin
 R1Ch=0;
 R2Ch=0;
 clk=0;
 Wch=0;
 RDin=0;
 RegWrite=1;
 end
   always
   begin
   #10 clk=~clk;
   end
   always
   begin
   #20 R2Ch=R2Ch+1;
   end
   always 
   begin
   #20 R1Ch=R1Ch+1;
   end
    RegFile REG2(clk,RDin,R1Ch,R2Ch,Wch,RegWrite,R1Data,MDin);
endmodule
