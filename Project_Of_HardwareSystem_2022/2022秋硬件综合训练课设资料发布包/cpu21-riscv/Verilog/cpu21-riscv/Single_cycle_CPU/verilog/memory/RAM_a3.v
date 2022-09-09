/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : RAM_a3                                                       **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module RAM_a3( addr,
               clk,
               d,
               we,
               q);

   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input[9:0]  addr;
   input  clk;
   input[7:0]  d;
   input  we;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output[7:0] q;

	reg [9:0] mem[31:0];
	always @ (posedge clk) begin
		if (we)
			mem[addr] <= d;
	end
	assign q = mem[addr];

endmodule
