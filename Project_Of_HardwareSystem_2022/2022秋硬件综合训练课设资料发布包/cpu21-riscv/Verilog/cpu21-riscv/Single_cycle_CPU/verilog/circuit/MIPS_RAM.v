/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : MIPS_RAM                                                     **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module MIPS_RAM( CLK,
                 Din,
                 MemWrite,
                 addres,
                 sel,
                 Dout);

   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input  CLK;
   input[31:0]  Din;
   input  MemWrite;
   input[9:0]  addres;
   input[3:0]  sel;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output[31:0] Dout;

   /***************************************************************************
    ** Here the internal wires are defined                                   **
    ***************************************************************************/
   wire[31:0] s_LOGISIM_BUS_14;
   wire[31:0] s_LOGISIM_BUS_20;
   wire[3:0] s_LOGISIM_BUS_4;
   wire[9:0] s_LOGISIM_BUS_5;
   wire s_LOGISIM_NET_0;
   wire s_LOGISIM_NET_1;
   wire s_LOGISIM_NET_10;
   wire s_LOGISIM_NET_11;
   wire s_LOGISIM_NET_12;
   wire s_LOGISIM_NET_2;
   wire s_LOGISIM_NET_3;
   wire s_LOGISIM_NET_6;
   wire s_LOGISIM_NET_7;
   wire s_LOGISIM_NET_8;
   wire s_LOGISIM_NET_9;


   /***************************************************************************
    ** Here all input connections are defined                                **
    ***************************************************************************/
   assign s_LOGISIM_BUS_4[3:0]               = sel;
   assign s_LOGISIM_NET_2                    = MemWrite;
   assign s_LOGISIM_NET_3                    = CLK;
   assign s_LOGISIM_BUS_5[9:0]               = addres;
   assign s_LOGISIM_BUS_20[31:0]             = Din;

   /***************************************************************************
    ** Here all output connections are defined                               **
    ***************************************************************************/
   assign Dout                               = s_LOGISIM_BUS_14[31:0];

   /***************************************************************************
    ** Here all normal components are defined                                **
    ***************************************************************************/
   Decoder_16      DECODER_1 (.DecoderOut_0(),
                              .DecoderOut_1(s_LOGISIM_NET_8),
                              .DecoderOut_10(),
                              .DecoderOut_11(),
                              .DecoderOut_12(),
                              .DecoderOut_13(),
                              .DecoderOut_14(),
                              .DecoderOut_15(s_LOGISIM_NET_1),
                              .DecoderOut_2(s_LOGISIM_NET_0),
                              .DecoderOut_3(),
                              .DecoderOut_4(s_LOGISIM_NET_6),
                              .DecoderOut_5(),
                              .DecoderOut_6(),
                              .DecoderOut_7(),
                              .DecoderOut_8(s_LOGISIM_NET_7),
                              .DecoderOut_9(),
                              .Enable(1'b1),
                              .Sel(s_LOGISIM_BUS_4[3:0]));

   RAM_a3      RAM_1 (.addr(s_LOGISIM_BUS_5[9:0]),
                      .clk(s_LOGISIM_NET_3),
                      .d(s_LOGISIM_BUS_20[7:0]),
                      .q(s_LOGISIM_BUS_14[7:0]),
                      .we(s_LOGISIM_NET_2),
                      .sel(s_LOGISIM_NET_9));

   RAM_a2      RAM_2 (.addr(s_LOGISIM_BUS_5[9:0]),
                      .clk(s_LOGISIM_NET_3),
                      .d(s_LOGISIM_BUS_20[15:8]),
                      .q(s_LOGISIM_BUS_14[15:8]),
                      .we(s_LOGISIM_NET_2),
                      .sel(s_LOGISIM_NET_10));

   OR_GATE #(.BubblesMask(0))
      GATE_1 (.Input_1(s_LOGISIM_NET_8),
              .Input_2(s_LOGISIM_NET_1),
              .Result(s_LOGISIM_NET_9));

   RAM_a1      RAM_3 (.addr(s_LOGISIM_BUS_5[9:0]),
                      .clk(s_LOGISIM_NET_3),
                      .d(s_LOGISIM_BUS_20[23:16]),
                      .q(s_LOGISIM_BUS_14[23:16]),
                      .we(s_LOGISIM_NET_2),
                      .sel(s_LOGISIM_NET_11));

   OR_GATE #(.BubblesMask(0))
      GATE_2 (.Input_1(s_LOGISIM_NET_6),
              .Input_2(s_LOGISIM_NET_1),
              .Result(s_LOGISIM_NET_11));

   OR_GATE #(.BubblesMask(0))
      GATE_3 (.Input_1(s_LOGISIM_NET_7),
              .Input_2(s_LOGISIM_NET_1),
              .Result(s_LOGISIM_NET_12));

   OR_GATE #(.BubblesMask(0))
      GATE_4 (.Input_1(s_LOGISIM_NET_0),
              .Input_2(s_LOGISIM_NET_1),
              .Result(s_LOGISIM_NET_10));

   RAM_a4      RAM_4 (.addr(s_LOGISIM_BUS_5[9:0]),
                      .clk(s_LOGISIM_NET_3),
                      .d(s_LOGISIM_BUS_20[31:24]),
                      .q(s_LOGISIM_BUS_14[31:24]),
                      .we(s_LOGISIM_NET_2),
                      .sel(s_LOGISIM_NET_12));



endmodule
