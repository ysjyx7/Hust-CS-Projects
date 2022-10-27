/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : Decoder_16                                                   **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module Decoder_16( Enable,
                   Sel,
                   DecoderOut_0,
                   DecoderOut_1,
                   DecoderOut_10,
                   DecoderOut_11,
                   DecoderOut_12,
                   DecoderOut_13,
                   DecoderOut_14,
                   DecoderOut_15,
                   DecoderOut_2,
                   DecoderOut_3,
                   DecoderOut_4,
                   DecoderOut_5,
                   DecoderOut_6,
                   DecoderOut_7,
                   DecoderOut_8,
                   DecoderOut_9);

   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input  Enable;
   input[3:0]  Sel;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output DecoderOut_0;
   output DecoderOut_1;
   output DecoderOut_10;
   output DecoderOut_11;
   output DecoderOut_12;
   output DecoderOut_13;
   output DecoderOut_14;
   output DecoderOut_15;
   output DecoderOut_2;
   output DecoderOut_3;
   output DecoderOut_4;
   output DecoderOut_5;
   output DecoderOut_6;
   output DecoderOut_7;
   output DecoderOut_8;
   output DecoderOut_9;
   assign DecoderOut_0  = (Enable&(Sel == 4'b0000)) ? 1'b1 : 1'b0;
   assign DecoderOut_1  = (Enable&(Sel == 4'b0001)) ? 1'b1 : 1'b0;
   assign DecoderOut_2  = (Enable&(Sel == 4'b0010)) ? 1'b1 : 1'b0;
   assign DecoderOut_3  = (Enable&(Sel == 4'b0011)) ? 1'b1 : 1'b0;
   assign DecoderOut_4  = (Enable&(Sel == 4'b0100)) ? 1'b1 : 1'b0;
   assign DecoderOut_5  = (Enable&(Sel == 4'b0101)) ? 1'b1 : 1'b0;
   assign DecoderOut_6  = (Enable&(Sel == 4'b0110)) ? 1'b1 : 1'b0;
   assign DecoderOut_7  = (Enable&(Sel == 4'b0111)) ? 1'b1 : 1'b0;
   assign DecoderOut_8  = (Enable&(Sel == 4'b1000)) ? 1'b1 : 1'b0;
   assign DecoderOut_9  = (Enable&(Sel == 4'b1001)) ? 1'b1 : 1'b0;
   assign DecoderOut_10 = (Enable&(Sel == 4'b1010)) ? 1'b1 : 1'b0;
   assign DecoderOut_11 = (Enable&(Sel == 4'b1011)) ? 1'b1 : 1'b0;
   assign DecoderOut_12 = (Enable&(Sel == 4'b1100)) ? 1'b1 : 1'b0;
   assign DecoderOut_13 = (Enable&(Sel == 4'b1101)) ? 1'b1 : 1'b0;
   assign DecoderOut_14 = (Enable&(Sel == 4'b1110)) ? 1'b1 : 1'b0;
   assign DecoderOut_15 = (Enable&(Sel == 4'b1111)) ? 1'b1 : 1'b0;

endmodule
