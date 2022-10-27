`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/10/26 19:22:08
// Design Name: 
// Module Name: Bit_Extender_7_32_UN
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


module Bit_Extender_7_32_UN(imm_in,
                                imm_out);

   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input[6:0]  imm_in;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output reg [31:0] imm_out;

	always @(*) begin
		imm_out = {25'b0000000000000000000000000, imm_in};
	end

endmodule
