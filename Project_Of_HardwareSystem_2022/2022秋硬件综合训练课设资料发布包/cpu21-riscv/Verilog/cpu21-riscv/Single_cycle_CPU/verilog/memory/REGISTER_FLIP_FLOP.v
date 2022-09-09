/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : REGISTER_FLIP_FLOP                                           **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module REGISTER_FLIP_FLOP( Clock,
                           ClockEnable,
                           D,
                           Reset,
                           Tick,
                           cs,
                           pre,
                           Q);

   /***************************************************************************
    ** Here all module parameters are defined with a dummy value             **
    ***************************************************************************/
   parameter ActiveLevel = 1;
   parameter NrOfBits = 1;


   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input  Clock;
   input  ClockEnable;
   input[NrOfBits-1:0]  D;
   input  Reset;
   input  Tick;
   input  cs;
   input  pre;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output[NrOfBits-1:0] Q;

   /***************************************************************************
    ** Here the internal registers are defined                               **
    ***************************************************************************/
   reg[NrOfBits-1:0] s_state_reg;
   reg[NrOfBits-1:0] s_state_reg_neg_edge;

   assign Q = cs? {NrOfBits{1'bz}} : ((ActiveLevel) ? s_state_reg : s_state_reg_neg_edge);

   always @(posedge Clock or posedge Reset or posedge pre)
   begin
      if (Reset) s_state_reg <= 0;
      else if(pre) s_state_reg <= {NrOfBits{1'b1}};
      else if (ClockEnable&Tick) s_state_reg <= D;
   end

   always @(negedge Clock or posedge Reset or posedge pre)
   begin
      if (Reset) s_state_reg_neg_edge <= 0;
      else if(pre) s_state_reg_neg_edge <= {NrOfBits{1'b1}};
      else if (ClockEnable&Tick) s_state_reg_neg_edge <= D;
   end

endmodule
