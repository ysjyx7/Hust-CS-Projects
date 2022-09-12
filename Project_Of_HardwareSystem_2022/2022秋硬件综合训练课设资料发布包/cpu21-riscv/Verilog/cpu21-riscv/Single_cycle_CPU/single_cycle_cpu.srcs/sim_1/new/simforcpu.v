`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/09/10 01:55:12
// Design Name: 
// Module Name: simforcpu
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


module simforcpu();
    reg clk,GO,rst;
    wire [7:0]SEG,AN;
    wire [31:0]leddata,PC,IR,R1Data;
  //  wire clk1khz;
    wire [31:0]RDin,Result,jalrin,AluBin;
    wire [4:0]R2ch,r1ch,Wch;
    wire ecall,halt,rst,Beq,BLTU,equal,branch;
    wire [3:0]AluOP;
    initial
    begin
        clk=0;
        rst=0;
        GO=0;
    end
    always
    begin 
        #5 clk=~clk;
    end
    single_cycle_cpu cpu(clk,rst,GO,AN,SEG,leddata,PC,IR,R1Data,ecall,R2ch,r1ch,Wch,RDin,jalrin,AluOP,Result,AluBin,halt,BLTU,equal,Beq,branch);
   // ,PC,IR,R2ch,Result,RDin,JAL,JALR,MDin,R1Data,ecall,r1ch,RegWrite,jalrin,Wch,AluBin);    
endmodule
