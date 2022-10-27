`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/09/08 07:12:37
// Design Name: 
// Module Name: Unsigned_cmp
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


module Unsigned_cmp(
            input [31:0] data1,
            input [31:0] data2,
            input _signed_flag,
            
            output reg compare_flag
);

always @(data1 or data2 or _signed_flag)begin
if(_signed_flag==1)begin
  if(data1[31]==1&&data2[31]==0)
    compare_flag=1;
  else if(data1[31]==0&&data2[31]==1)
    compare_flag=0;
  else if(data1[31]==1&&data2[31]==1)
     compare_flag = (data1>data2) ? 1 : 0;
  else
      compare_flag = (data1<data2) ? 1 : 0 ;end
else if(_signed_flag==0)  begin
   compare_flag = (data1<data2) ? 1 : 0 ; end
else begin
    compare_flag =1'bz; end
    end
endmodule
