/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : RegFile                                                      **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module RegFile( CLK,
                Din,
                R1opt,
                R2opt,
                W,
                WE,
                R1,
                R2);

   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input  CLK;
   input[31:0]  Din;
   input[4:0]  R1opt;
   input[4:0]  R2opt;
   input[4:0]  W;
   input  WE;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output[31:0] R1;
   output[31:0] R2;

   /***************************************************************************
    ** Here the internal wires are defined                                   **
    ***************************************************************************/
   wire[31:0] s_LOGISIM_BUS_1;
   wire[31:0] s_LOGISIM_BUS_10;
   wire[31:0] s_LOGISIM_BUS_11;
   wire[31:0] s_LOGISIM_BUS_12;
   wire[31:0] s_LOGISIM_BUS_13;
   wire[31:0] s_LOGISIM_BUS_14;
   wire[31:0] s_LOGISIM_BUS_15;
   wire[31:0] s_LOGISIM_BUS_16;
   wire[31:0] s_LOGISIM_BUS_18;
   wire[31:0] s_LOGISIM_BUS_19;
   wire[31:0] s_LOGISIM_BUS_2;
   wire[31:0] s_LOGISIM_BUS_23;
   wire[31:0] s_LOGISIM_BUS_26;
   wire[31:0] s_LOGISIM_BUS_27;
   wire[31:0] s_LOGISIM_BUS_31;
   wire[31:0] s_LOGISIM_BUS_33;
   wire[31:0] s_LOGISIM_BUS_34;
   wire[31:0] s_LOGISIM_BUS_39;
   wire[31:0] s_LOGISIM_BUS_40;
   wire[31:0] s_LOGISIM_BUS_41;
   wire[31:0] s_LOGISIM_BUS_43;
   wire[31:0] s_LOGISIM_BUS_44;
   wire[31:0] s_LOGISIM_BUS_45;
   wire[31:0] s_LOGISIM_BUS_46;
   wire[31:0] s_LOGISIM_BUS_47;
   wire[31:0] s_LOGISIM_BUS_48;
   wire[31:0] s_LOGISIM_BUS_50;
   wire[31:0] s_LOGISIM_BUS_51;
   wire[31:0] s_LOGISIM_BUS_55;
   wire[4:0] s_LOGISIM_BUS_57;
   wire[31:0] s_LOGISIM_BUS_59;
   wire[4:0] s_LOGISIM_BUS_60;
   wire[31:0] s_LOGISIM_BUS_63;
   wire[31:0] s_LOGISIM_BUS_64;
   wire[31:0] s_LOGISIM_BUS_65;
   wire[31:0] s_LOGISIM_BUS_69;
   wire[31:0] s_LOGISIM_BUS_70;
   wire[4:0] s_LOGISIM_BUS_71;
   wire[31:0] s_LOGISIM_BUS_8;
   wire s_LOGISIM_NET_0;
   wire s_LOGISIM_NET_17;
   wire s_LOGISIM_NET_20;
   wire s_LOGISIM_NET_21;
   wire s_LOGISIM_NET_22;
   wire s_LOGISIM_NET_24;
   wire s_LOGISIM_NET_25;
   wire s_LOGISIM_NET_28;
   wire s_LOGISIM_NET_29;
   wire s_LOGISIM_NET_3;
   wire s_LOGISIM_NET_30;
   wire s_LOGISIM_NET_32;
   wire s_LOGISIM_NET_35;
   wire s_LOGISIM_NET_36;
   wire s_LOGISIM_NET_37;
   wire s_LOGISIM_NET_38;
   wire s_LOGISIM_NET_4;
   wire s_LOGISIM_NET_42;
   wire s_LOGISIM_NET_49;
   wire s_LOGISIM_NET_5;
   wire s_LOGISIM_NET_52;
   wire s_LOGISIM_NET_53;
   wire s_LOGISIM_NET_54;
   wire s_LOGISIM_NET_56;
   wire s_LOGISIM_NET_58;
   wire s_LOGISIM_NET_6;
   wire s_LOGISIM_NET_61;
   wire s_LOGISIM_NET_62;
   wire s_LOGISIM_NET_66;
   wire s_LOGISIM_NET_67;
   wire s_LOGISIM_NET_68;
   wire s_LOGISIM_NET_7;
   wire s_LOGISIM_NET_72;
   wire s_LOGISIM_NET_9;


   /***************************************************************************
    ** Here all input connections are defined                                **
    ***************************************************************************/
   assign s_LOGISIM_BUS_60[4:0]              = W;
   assign s_LOGISIM_NET_9                    = CLK;
   assign s_LOGISIM_NET_53                   = WE;
   assign s_LOGISIM_BUS_15[31:0]             = Din;
   assign s_LOGISIM_BUS_71[4:0]              = R2opt;
   assign s_LOGISIM_BUS_57[4:0]              = R1opt;

   /***************************************************************************
    ** Here all output connections are defined                               **
    ***************************************************************************/
   assign R2                                 = s_LOGISIM_BUS_39[31:0];
   assign R1                                 = s_LOGISIM_BUS_70[31:0];

   /***************************************************************************
    ** Here all in-lined components are defined                              **
    ***************************************************************************/
   assign s_LOGISIM_BUS_51[31:0] = 32'd0;


   /***************************************************************************
    ** Here all normal components are defined                                **
    ***************************************************************************/
   Demultiplexer_32      DEMUX_1 (.DemuxIn(s_LOGISIM_NET_53),
                                  .DemuxOut_0(s_LOGISIM_NET_62),
                                  .DemuxOut_1(s_LOGISIM_NET_4),
                                  .DemuxOut_10(s_LOGISIM_NET_54),
                                  .DemuxOut_11(s_LOGISIM_NET_37),
                                  .DemuxOut_12(s_LOGISIM_NET_68),
                                  .DemuxOut_13(s_LOGISIM_NET_58),
                                  .DemuxOut_14(s_LOGISIM_NET_3),
                                  .DemuxOut_15(s_LOGISIM_NET_0),
                                  .DemuxOut_16(s_LOGISIM_NET_7),
                                  .DemuxOut_17(s_LOGISIM_NET_6),
                                  .DemuxOut_18(s_LOGISIM_NET_17),
                                  .DemuxOut_19(s_LOGISIM_NET_21),
                                  .DemuxOut_2(s_LOGISIM_NET_29),
                                  .DemuxOut_20(s_LOGISIM_NET_20),
                                  .DemuxOut_21(s_LOGISIM_NET_24),
                                  .DemuxOut_22(s_LOGISIM_NET_22),
                                  .DemuxOut_23(s_LOGISIM_NET_25),
                                  .DemuxOut_24(s_LOGISIM_NET_32),
                                  .DemuxOut_25(s_LOGISIM_NET_30),
                                  .DemuxOut_26(s_LOGISIM_NET_35),
                                  .DemuxOut_27(s_LOGISIM_NET_38),
                                  .DemuxOut_28(s_LOGISIM_NET_36),
                                  .DemuxOut_29(s_LOGISIM_NET_42),
                                  .DemuxOut_3(s_LOGISIM_NET_66),
                                  .DemuxOut_30(s_LOGISIM_NET_5),
                                  .DemuxOut_31(s_LOGISIM_NET_28),
                                  .DemuxOut_4(s_LOGISIM_NET_49),
                                  .DemuxOut_5(s_LOGISIM_NET_72),
                                  .DemuxOut_6(s_LOGISIM_NET_61),
                                  .DemuxOut_7(s_LOGISIM_NET_52),
                                  .DemuxOut_8(s_LOGISIM_NET_56),
                                  .DemuxOut_9(s_LOGISIM_NET_67),
                                  .Enable(1'b1),
                                  .Sel(s_LOGISIM_BUS_60[4:0]));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_1 (.Clock(s_LOGISIM_NET_9),
                       .ClockEnable(s_LOGISIM_NET_30),
                       .D(s_LOGISIM_BUS_15[31:0]),
                       .Q(s_LOGISIM_BUS_12[31:0]),
                       .Reset(1'b0),
                       .Tick(1'b1),
                       .cs(1'b1),
                       .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_2 (.Clock(s_LOGISIM_NET_9),
                       .ClockEnable(s_LOGISIM_NET_52),
                       .D(s_LOGISIM_BUS_15[31:0]),
                       .Q(s_LOGISIM_BUS_44[31:0]),
                       .Reset(1'b0),
                       .Tick(1'b1),
                       .cs(1'b1),
                       .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_3 (.Clock(s_LOGISIM_NET_9),
                       .ClockEnable(s_LOGISIM_NET_21),
                       .D(s_LOGISIM_BUS_15[31:0]),
                       .Q(s_LOGISIM_BUS_63[31:0]),
                       .Reset(1'b0),
                       .Tick(1'b1),
                       .cs(1'b1),
                       .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_4 (.Clock(s_LOGISIM_NET_9),
                       .ClockEnable(s_LOGISIM_NET_72),
                       .D(s_LOGISIM_BUS_15[31:0]),
                       .Q(s_LOGISIM_BUS_26[31:0]),
                       .Reset(1'b0),
                       .Tick(1'b1),
                       .cs(1'b1),
                       .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_5 (.Clock(s_LOGISIM_NET_9),
                       .ClockEnable(s_LOGISIM_NET_20),
                       .D(s_LOGISIM_BUS_15[31:0]),
                       .Q(s_LOGISIM_BUS_8[31:0]),
                       .Reset(1'b0),
                       .Tick(1'b1),
                       .cs(1'b1),
                       .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_6 (.Clock(s_LOGISIM_NET_9),
                       .ClockEnable(s_LOGISIM_NET_49),
                       .D(s_LOGISIM_BUS_15[31:0]),
                       .Q(s_LOGISIM_BUS_2[31:0]),
                       .Reset(1'b0),
                       .Tick(1'b1),
                       .cs(1'b1),
                       .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_7 (.Clock(s_LOGISIM_NET_9),
                       .ClockEnable(s_LOGISIM_NET_28),
                       .D(s_LOGISIM_BUS_15[31:0]),
                       .Q(s_LOGISIM_BUS_59[31:0]),
                       .Reset(1'b0),
                       .Tick(1'b1),
                       .cs(1'b1),
                       .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_8 (.Clock(s_LOGISIM_NET_9),
                       .ClockEnable(s_LOGISIM_NET_37),
                       .D(s_LOGISIM_BUS_15[31:0]),
                       .Q(s_LOGISIM_BUS_27[31:0]),
                       .Reset(1'b0),
                       .Tick(1'b1),
                       .cs(1'b1),
                       .pre(1'b1));

   Multiplexer_bus_32 #(.NrOfBits(32))
      MUX_1 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_14[31:0]),
             .MuxIn_1(s_LOGISIM_BUS_69[31:0]),
             .MuxIn_10(s_LOGISIM_BUS_45[31:0]),
             .MuxIn_11(s_LOGISIM_BUS_27[31:0]),
             .MuxIn_12(s_LOGISIM_BUS_11[31:0]),
             .MuxIn_13(s_LOGISIM_BUS_41[31:0]),
             .MuxIn_14(s_LOGISIM_BUS_64[31:0]),
             .MuxIn_15(s_LOGISIM_BUS_55[31:0]),
             .MuxIn_16(s_LOGISIM_BUS_10[31:0]),
             .MuxIn_17(s_LOGISIM_BUS_34[31:0]),
             .MuxIn_18(s_LOGISIM_BUS_50[31:0]),
             .MuxIn_19(s_LOGISIM_BUS_63[31:0]),
             .MuxIn_2(s_LOGISIM_BUS_47[31:0]),
             .MuxIn_20(s_LOGISIM_BUS_8[31:0]),
             .MuxIn_21(s_LOGISIM_BUS_40[31:0]),
             .MuxIn_22(s_LOGISIM_BUS_23[31:0]),
             .MuxIn_23(s_LOGISIM_BUS_46[31:0]),
             .MuxIn_24(s_LOGISIM_BUS_1[31:0]),
             .MuxIn_25(s_LOGISIM_BUS_12[31:0]),
             .MuxIn_26(s_LOGISIM_BUS_18[31:0]),
             .MuxIn_27(s_LOGISIM_BUS_19[31:0]),
             .MuxIn_28(s_LOGISIM_BUS_16[31:0]),
             .MuxIn_29(s_LOGISIM_BUS_43[31:0]),
             .MuxIn_3(s_LOGISIM_BUS_65[31:0]),
             .MuxIn_30(s_LOGISIM_BUS_48[31:0]),
             .MuxIn_31(s_LOGISIM_BUS_59[31:0]),
             .MuxIn_4(s_LOGISIM_BUS_2[31:0]),
             .MuxIn_5(s_LOGISIM_BUS_26[31:0]),
             .MuxIn_6(s_LOGISIM_BUS_33[31:0]),
             .MuxIn_7(s_LOGISIM_BUS_44[31:0]),
             .MuxIn_8(s_LOGISIM_BUS_13[31:0]),
             .MuxIn_9(s_LOGISIM_BUS_31[31:0]),
             .MuxOut(s_LOGISIM_BUS_70[31:0]),
             .Sel(s_LOGISIM_BUS_57[4:0]));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_9 (.Clock(s_LOGISIM_NET_9),
                       .ClockEnable(s_LOGISIM_NET_6),
                       .D(s_LOGISIM_BUS_15[31:0]),
                       .Q(s_LOGISIM_BUS_34[31:0]),
                       .Reset(1'b0),
                       .Tick(1'b1),
                       .cs(1'b1),
                       .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_10 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_42),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_43[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_11 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_38),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_19[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_12 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_66),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_65[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_13 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_7),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_10[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_14 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_32),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_1[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_15 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_22),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_23[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_16 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_17),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_50[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_17 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_24),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_40[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_18 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_4),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_69[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_19 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_68),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_11[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_20 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_67),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_31[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_21 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_35),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_18[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_22 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_25),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_46[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_23 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_36),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_16[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   Multiplexer_bus_32 #(.NrOfBits(32))
      MUX_2 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_14[31:0]),
             .MuxIn_1(s_LOGISIM_BUS_69[31:0]),
             .MuxIn_10(s_LOGISIM_BUS_45[31:0]),
             .MuxIn_11(s_LOGISIM_BUS_27[31:0]),
             .MuxIn_12(s_LOGISIM_BUS_11[31:0]),
             .MuxIn_13(s_LOGISIM_BUS_41[31:0]),
             .MuxIn_14(s_LOGISIM_BUS_64[31:0]),
             .MuxIn_15(s_LOGISIM_BUS_55[31:0]),
             .MuxIn_16(s_LOGISIM_BUS_10[31:0]),
             .MuxIn_17(s_LOGISIM_BUS_34[31:0]),
             .MuxIn_18(s_LOGISIM_BUS_50[31:0]),
             .MuxIn_19(s_LOGISIM_BUS_63[31:0]),
             .MuxIn_2(s_LOGISIM_BUS_47[31:0]),
             .MuxIn_20(s_LOGISIM_BUS_8[31:0]),
             .MuxIn_21(s_LOGISIM_BUS_40[31:0]),
             .MuxIn_22(s_LOGISIM_BUS_23[31:0]),
             .MuxIn_23(s_LOGISIM_BUS_46[31:0]),
             .MuxIn_24(s_LOGISIM_BUS_1[31:0]),
             .MuxIn_25(s_LOGISIM_BUS_12[31:0]),
             .MuxIn_26(s_LOGISIM_BUS_18[31:0]),
             .MuxIn_27(s_LOGISIM_BUS_19[31:0]),
             .MuxIn_28(s_LOGISIM_BUS_16[31:0]),
             .MuxIn_29(s_LOGISIM_BUS_43[31:0]),
             .MuxIn_3(s_LOGISIM_BUS_65[31:0]),
             .MuxIn_30(s_LOGISIM_BUS_48[31:0]),
             .MuxIn_31(s_LOGISIM_BUS_59[31:0]),
             .MuxIn_4(s_LOGISIM_BUS_2[31:0]),
             .MuxIn_5(s_LOGISIM_BUS_26[31:0]),
             .MuxIn_6(s_LOGISIM_BUS_33[31:0]),
             .MuxIn_7(s_LOGISIM_BUS_44[31:0]),
             .MuxIn_8(s_LOGISIM_BUS_13[31:0]),
             .MuxIn_9(s_LOGISIM_BUS_31[31:0]),
             .MuxOut(s_LOGISIM_BUS_39[31:0]),
             .Sel(s_LOGISIM_BUS_71[4:0]));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_24 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_62),
                        .D(s_LOGISIM_BUS_51[31:0]),
                        .Q(s_LOGISIM_BUS_14[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_25 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_54),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_45[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_26 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_56),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_13[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_27 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_58),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_41[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_28 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_0),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_55[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_29 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_29),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_47[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_30 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_5),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_48[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_31 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_61),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_33[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));

   REGISTER_FLIP_FLOP_sb #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_32 (.Clock(s_LOGISIM_NET_9),
                        .ClockEnable(s_LOGISIM_NET_3),
                        .D(s_LOGISIM_BUS_15[31:0]),
                        .Q(s_LOGISIM_BUS_64[31:0]),
                        .Reset(1'b0),
                        .Tick(1'b1),
                        .cs(1'b1),
                        .pre(1'b1));



endmodule
