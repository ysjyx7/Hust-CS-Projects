`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/09/08 05:45:38
// Design Name: 
// Module Name: single_cycle_cpu
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


module single_cycle_cpu(min,mid,max,clk_500M,rst,go,AN,SEG);
//,ledData,PC,IR,R1Data,ecall,R2Ch,R1Ch,Wch,RDin,jalrin,AluOP,Result,AluBin,halt,BLTU,equal,Beq,branch);
input clk_500M;
input rst;
input go;
input min,mid,max;
output [7:0] AN,SEG;
//output [31:0] ledData,PC,IR,R1Data,RDin,jalrin,Result,AluBin;
//output ecall;
//output AluOP;
//output halt,BLTU,equal,Beq,branch;
//output [4:0]R1Ch,R2Ch,Wch;
wire [31:0]PC,PCnext,jalrin,R1Data,branchdata,jaldata,MDin,mul1,mul2,mul3,IR,RDin,MulImmout,Din,Dout,ledData;
wire JALR,JAL,branch,SB,BLTU,ecall,S_type,MemToReg,MemWrite,AluSrcB,RegWrite,Beq,Bne,CSRRCI,CSRRSI,uret,equal;
wire [1:0]select;
wire [3:0]AluOP,sel,s1;
wire [4:0]R1Ch,R2Ch,mul24_20,Wch,D1,D2;
wire [11:0]MulImm;
wire [31:0]AluBin,Result,Result2,B2,J2,D3,RD1;
wire less,nol,halt,Less;
wire [11:0]B1;
wire [19:0]J1;
wire clk_mid;
wire clk_min;
wire clk_max;
reg clk;
wire [2:0]choose;
assign choose={max,mid,min};
divider #(5000000) Ddd0(clk_500M,clk_min);
divider #(2500000) Ddd1(clk_500M,clk_mid);
divider #(1000000) Ddd2(clk_500M,clk_max);
always@(choose)
begin
    case(choose)
    3'b001:
    clk<=clk_min;
    3'b100:
    clk<=clk_max;
    default:
    clk<=clk_mid;
    endcase
  end

assign PCnext=PC+4;


Multiplexer_bus_2 #(32) M1(1'b1,PCnext,32'hfffffffe&(jalrin+R1Data),JALR,mul1);
Multiplexer_bus_2 #(32) M2(1'b1,mul1,jaldata,JAL,mul2);
Multiplexer_bus_2 #(32) M3(1'b1,mul2,branchdata,branch,mul3);
REGISTER_FLIP_FLOP_PC REG1(clk,!halt,mul3,rst,1'b1,1'b0,1'b0,PC);
ROM_ROM ROM1(PC[11:2],IR);
yingbuxian YBX1({IR[30:30],IR[25:25],IR[14:12]},IR[21:21],IR[6:2],AluOP,AluSrcB,BLTU,Beq,Bne,CSRRCI,CSRRSI,JAL,JALR,MemToReg,MemWrite,RegWrite,SB,S_type,ecall,uret);
Multiplexer_bus_2 #(5) M4(1'b1,IR[19:15],5'h11,ecall,R1Ch);
Multiplexer_bus_2 #(5) M5(1'b1,IR[24:20],5'h01,JALR,mul24_20);
Multiplexer_bus_2 #(5) M6(1'b1,mul24_20,5'h0a,ecall,R2Ch);
Multiplexer_bus_2 #(5) M7(1'b1,IR[11:7],5'h01,JALR,Wch);
RegFile REG2(clk,RDin,R1Ch,R2Ch,Wch,RegWrite,R1Data,MDin);
Multiplexer_bus_2 #(12) M8(1'b1,IR[31:20],{IR[31:25],IR[11:7]},S_type,MulImm);
Bit_Extender_12_32_SIGN BIT1(MulImm,jalrin);
Multiplexer_bus_2 #(32) M9(1'b1,MDin,jalrin,AluSrcB,AluBin);
ALU _ALU(AluOP,R1Data,AluBin,less,equal,Result,Result2,nol);
Unsigned_cmp UCMP(R1Data,MDin,1'b0,Less);
assign branch=(Beq&&equal)||(Bne&&!equal)||(BLTU&&Less);
assign B1={IR[31:31],IR[7:7],IR[30:25],IR[11:8]}<<4'h1;
Bit_Extender_12_32_SIGN BIT2(B1,B2);
assign branchdata=PC+B2;
assign J1={IR[31:31],IR[19:12],IR[20:20],IR[30:21]}<<5'h01;
Bit_Extender_20_32_SIGN BIT3(J1,J2);
assign jaldata=PC+J2;
assign select=Result[1:0];
Bit_Extender_2_5_SIGN BIT4(select,D1);
assign D2=D1<<3'h3;
Multiplexer_bus_2 #(32) M10(1'b1,MDin,MDin<<D2,SB,Din);
Multiplexer_bus_4 #(4) M11(1'b1,4'h1,4'h2,4'h4,4'h8,select,s1);
Multiplexer_bus_2 #(4) M13(1'b1,4'hf,s1,SB,sel);
MIPS_RAM RAM(clk,Din,MemWrite,Result[11:2],sel,Dout);
Multiplexer_bus_2 #(32) M14(1'b1,Result,PCnext,JAL||JALR,RD1);
Multiplexer_bus_2 #(32) M15(1'b1,RD1,Dout,MemToReg,RDin);
REGISTER_FLIP_FLOP #(.NrOfBits(1)) R0(clk,!halt,ecall&&!(R1Data==32'h22),go,1'b1,1'b0,1'b0,halt);
REGISTER_FLIP_FLOP #(.NrOfBits(32)) RSB(clk,ecall&&(R1Data==32'h22),MDin,1'b0,1'b1,1'b0,1'b0,ledData);
display sbdis(clk_500M,ledData,AN,SEG);
endmodule
