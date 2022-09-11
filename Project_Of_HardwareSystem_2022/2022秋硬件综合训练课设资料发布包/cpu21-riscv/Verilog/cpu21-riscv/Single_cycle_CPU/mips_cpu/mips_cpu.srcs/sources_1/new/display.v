`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/09/08 15:55:28
// Design Name: 
// Module Name: display
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


module display(clk,leddata,AN,SEG);
input clk;
input [31:0]leddata;
output reg[7:0]AN,SEG;
wire [3:0]y7,y6,y5,y4,y3,y2,y1,y0;
reg [3:0]y;
assign {y7,y6,y5,y4,y3,y2,y1,y0}=leddata;
//wire clk_1khz;
//divider#(50_000) d1(clk,clk_1khz);
reg [2:0]flag;
initial 
begin
flag=0;
y=0;
end
always@(posedge clk)
    flag = (flag+1)%8;
always@(flag)
begin
    case(flag)
    3'b000:
    begin
        AN <= 8'b1111_1110;
        y <= y0;
    end
    3'b001:
    begin
        AN <= 8'b1111_1101;
        y <= y1;
    end
    3'b010:
    begin
        AN <= 8'b1111_1011;
        y <= y2;
    end
    3'b011:
    begin
        AN <= 8'b1111_0111;
        y <= y3;
    end
    3'b100:
    begin
        AN <= 8'b1110_1111;
        y <= y4;
    end
    3'b101:
    begin
        AN <= 8'b1101_1111;
        y <= y5;
    end
    3'b110:
    begin
        AN <= 8'b1011_1111;
        y <= y6;
    end
    3'b111:
    begin
        AN <= 8'b0111_1111;
        y <= y7;
    end
    endcase
end
always @(y[3:0])
     begin
      case(y[3:0])
             4'b0000 : SEG[7:0] = 8'b11000000;
             4'b0001 : SEG[7:0] = 8'b11111001;
             4'b0010 : SEG[7:0] = 8'b10100100;
             4'b0011 : SEG[7:0] = 8'b10110000;
             4'b0100 : SEG[7:0] = 8'b10011001;
             4'b0101 : SEG[7:0] = 8'b10010010;
             4'b0110 : SEG[7:0] = 8'b10000010;
             4'b0111 : SEG[7:0] = 8'b11111000;
             4'b1000 : SEG[7:0] = 8'b10000000;
             4'b1001 : SEG[7:0] = 8'b10011000;
             4'b1010 : SEG[7:0] = 8'b10001000;
             4'b1011 : SEG[7:0] = 8'b10000011;
             4'b1100 : SEG[7:0] = 8'b11000110;
             4'b1101 : SEG[7:0] = 8'b10100001;
             4'b1110 : SEG[7:0] = 8'b10000110;
             default  : SEG[7:0] = 8'b10001110;
       endcase 
      end
endmodule
