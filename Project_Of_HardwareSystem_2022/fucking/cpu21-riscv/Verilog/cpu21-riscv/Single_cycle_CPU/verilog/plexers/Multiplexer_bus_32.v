/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : Multiplexer_bus_32                                           **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module Multiplexer_bus_32( Enable,
                           MuxIn_0,
                           MuxIn_1,
                           MuxIn_10,
                           MuxIn_11,
                           MuxIn_12,
                           MuxIn_13,
                           MuxIn_14,
                           MuxIn_15,
                           MuxIn_16,
                           MuxIn_17,
                           MuxIn_18,
                           MuxIn_19,
                           MuxIn_2,
                           MuxIn_20,
                           MuxIn_21,
                           MuxIn_22,
                           MuxIn_23,
                           MuxIn_24,
                           MuxIn_25,
                           MuxIn_26,
                           MuxIn_27,
                           MuxIn_28,
                           MuxIn_29,
                           MuxIn_3,
                           MuxIn_30,
                           MuxIn_31,
                           MuxIn_4,
                           MuxIn_5,
                           MuxIn_6,
                           MuxIn_7,
                           MuxIn_8,
                           MuxIn_9,
                           Sel,
                           MuxOut);

   /***************************************************************************
    ** Here all module parameters are defined with a dummy value             **
    ***************************************************************************/
   parameter NrOfBits = 1;


   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input  Enable;
   input[NrOfBits-1:0]  MuxIn_0;
   input[NrOfBits-1:0]  MuxIn_1;
   input[NrOfBits-1:0]  MuxIn_10;
   input[NrOfBits-1:0]  MuxIn_11;
   input[NrOfBits-1:0]  MuxIn_12;
   input[NrOfBits-1:0]  MuxIn_13;
   input[NrOfBits-1:0]  MuxIn_14;
   input[NrOfBits-1:0]  MuxIn_15;
   input[NrOfBits-1:0]  MuxIn_16;
   input[NrOfBits-1:0]  MuxIn_17;
   input[NrOfBits-1:0]  MuxIn_18;
   input[NrOfBits-1:0]  MuxIn_19;
   input[NrOfBits-1:0]  MuxIn_2;
   input[NrOfBits-1:0]  MuxIn_20;
   input[NrOfBits-1:0]  MuxIn_21;
   input[NrOfBits-1:0]  MuxIn_22;
   input[NrOfBits-1:0]  MuxIn_23;
   input[NrOfBits-1:0]  MuxIn_24;
   input[NrOfBits-1:0]  MuxIn_25;
   input[NrOfBits-1:0]  MuxIn_26;
   input[NrOfBits-1:0]  MuxIn_27;
   input[NrOfBits-1:0]  MuxIn_28;
   input[NrOfBits-1:0]  MuxIn_29;
   input[NrOfBits-1:0]  MuxIn_3;
   input[NrOfBits-1:0]  MuxIn_30;
   input[NrOfBits-1:0]  MuxIn_31;
   input[NrOfBits-1:0]  MuxIn_4;
   input[NrOfBits-1:0]  MuxIn_5;
   input[NrOfBits-1:0]  MuxIn_6;
   input[NrOfBits-1:0]  MuxIn_7;
   input[NrOfBits-1:0]  MuxIn_8;
   input[NrOfBits-1:0]  MuxIn_9;
   input[4:0]  Sel;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output[NrOfBits-1:0] MuxOut;

   /***************************************************************************
    ** Here the internal registers are defined                               **
    ***************************************************************************/
   reg[NrOfBits-1:0] s_selected_vector;

   assign MuxOut = s_selected_vector;

   always @(*)
   begin
      if (~Enable) s_selected_vector <= 0;
      else case (Sel)
         5'b00000:
            s_selected_vector <= MuxIn_0;
         5'b00001:
            s_selected_vector <= MuxIn_1;
         5'b00010:
            s_selected_vector <= MuxIn_2;
         5'b00011:
            s_selected_vector <= MuxIn_3;
         5'b00100:
            s_selected_vector <= MuxIn_4;
         5'b00101:
            s_selected_vector <= MuxIn_5;
         5'b00110:
            s_selected_vector <= MuxIn_6;
         5'b00111:
            s_selected_vector <= MuxIn_7;
         5'b01000:
            s_selected_vector <= MuxIn_8;
         5'b01001:
            s_selected_vector <= MuxIn_9;
         5'b01010:
            s_selected_vector <= MuxIn_10;
         5'b01011:
            s_selected_vector <= MuxIn_11;
         5'b01100:
            s_selected_vector <= MuxIn_12;
         5'b01101:
            s_selected_vector <= MuxIn_13;
         5'b01110:
            s_selected_vector <= MuxIn_14;
         5'b01111:
            s_selected_vector <= MuxIn_15;
         5'b10000:
            s_selected_vector <= MuxIn_16;
         5'b10001:
            s_selected_vector <= MuxIn_17;
         5'b10010:
            s_selected_vector <= MuxIn_18;
         5'b10011:
            s_selected_vector <= MuxIn_19;
         5'b10100:
            s_selected_vector <= MuxIn_20;
         5'b10101:
            s_selected_vector <= MuxIn_21;
         5'b10110:
            s_selected_vector <= MuxIn_22;
         5'b10111:
            s_selected_vector <= MuxIn_23;
         5'b11000:
            s_selected_vector <= MuxIn_24;
         5'b11001:
            s_selected_vector <= MuxIn_25;
         5'b11010:
            s_selected_vector <= MuxIn_26;
         5'b11011:
            s_selected_vector <= MuxIn_27;
         5'b11100:
            s_selected_vector <= MuxIn_28;
         5'b11101:
            s_selected_vector <= MuxIn_29;
         5'b11110:
            s_selected_vector <= MuxIn_30;
         default:
            s_selected_vector <= MuxIn_31;
      endcase
   end

endmodule
