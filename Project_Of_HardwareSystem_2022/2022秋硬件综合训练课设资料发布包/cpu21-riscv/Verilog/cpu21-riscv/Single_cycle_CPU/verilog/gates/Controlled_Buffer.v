/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : Controlled_Buffer                                            **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module Controlled_Buffer( Data_T,
                          Data_in,
                          Data_out);

   /***************************************************************************
    ** Here all module parameters are defined with a dummy value             **
    ***************************************************************************/
   parameter NrOfBits = 1;


   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input  Data_T;
   input  Data_in;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output Data_out;
   assign Data_out = Data_T? Data_in : {NrOfBits{1'bz}};

endmodule
