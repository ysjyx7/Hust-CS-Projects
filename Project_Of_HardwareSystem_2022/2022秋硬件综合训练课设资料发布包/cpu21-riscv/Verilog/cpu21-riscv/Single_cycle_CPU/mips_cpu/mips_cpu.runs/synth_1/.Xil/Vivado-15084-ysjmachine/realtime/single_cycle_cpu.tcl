# 
# Synthesis run script generated by Vivado
# 

namespace eval rt {
    variable rc
}
set rt::rc [catch {
  uplevel #0 {
    set ::env(BUILTIN_SYNTH) true
    source $::env(HRT_TCL_PATH)/rtSynthPrep.tcl
    rt::HARTNDb_resetJobStats
    rt::HARTNDb_resetSystemStats
    rt::HARTNDb_startSystemStats
    rt::HARTNDb_startJobStats
    set rt::cmdEcho 0
    rt::set_parameter writeXmsg true
    rt::set_parameter enableParallelHelperSpawn true
    set ::env(RT_TMP) "D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/mips_cpu/mips_cpu.runs/synth_1/.Xil/Vivado-15084-ysjmachine/realtime/tmp"
    if { [ info exists ::env(RT_TMP) ] } {
      file delete -force $::env(RT_TMP)
      file mkdir $::env(RT_TMP)
    }

    rt::delete_design

    rt::set_parameter datapathDensePacking false
    set rt::partid xc7a100tcsg324-1
    source $::env(HRT_TCL_PATH)/rtSynthParallelPrep.tcl
     file delete -force synth_hints.os

    set rt::multiChipSynthesisFlow false
    source $::env(SYNTH_COMMON)/common.tcl
    set rt::defaultWorkLibName xil_defaultlib

    set rt::useElabCache false
    if {$rt::useElabCache == false} {
      rt::read_verilog {
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/circuit/ALU.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/gates/AND_GATE.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/gates/AND_GATE_10_INPUTS.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/gates/AND_GATE_5_INPUTS.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/gates/AND_GATE_6_INPUTS.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/gates/AND_GATE_7_INPUTS.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/gates/AND_GATE_8_INPUTS.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/gates/AND_GATE_9_INPUTS.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/gates/AND_GATE_BUS.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/arithmetic/Adder.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/wiring/Bit_Extender_12_32_SIGN.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/wiring/Bit_Extender_20_32_SIGN.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/wiring/Bit_Extender_2_5_SIGN.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/arithmetic/Comparator.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/plexers/Decoder_16.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/plexers/Demultiplexer_32.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/circuit/MIPS_RAM.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/plexers/Multiplexer_16.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/plexers/Multiplexer_bus_16.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/plexers/Multiplexer_bus_2.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/plexers/Multiplexer_bus_32.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/plexers/Multiplexer_bus_4.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/gates/NOR_GATE_BUS.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/gates/NOT_GATE.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/gates/OR_GATE.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/gates/OR_GATE_10_INPUTS.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/gates/OR_GATE_11_INPUTS.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/gates/OR_GATE_3_INPUTS.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/gates/OR_GATE_4_INPUTS.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/gates/OR_GATE_7_INPUTS.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/gates/OR_GATE_8_INPUTS.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/gates/OR_GATE_BUS.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/memory/RAM_a1.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/memory/RAM_a2.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/memory/RAM_a3.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/memory/RAM_a4.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/memory/REGISTER_FLIP_FLOP.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/memory/REGISTER_FLIP_FLOP_PC.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/memory/REGISTER_FLIP_FLOP_sb.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/memory/ROM_ROM.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/circuit/RegFile.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/arithmetic/Shifter_32_bit.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/arithmetic/Subtractor.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/mips_cpu/mips_cpu.srcs/sources_1/new/Unsigned_cmp.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/gates/XOR_GATE_BUS.v
      D:/QQ/QQmsg/2849458605/FileRecv/display.v
      D:/QQ/QQmsg/2849458605/FileRecv/divider.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/circuit/help1.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/circuit/help2.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/verilog/circuit/yingbuxian.v
      D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/mips_cpu/mips_cpu.srcs/sources_1/new/single_cycle_cpu.v
    }
      rt::filesetChecksum
    }
    rt::set_parameter usePostFindUniquification false
    set rt::top single_cycle_cpu
    rt::set_parameter enableIncremental true
    rt::set_parameter markDebugPreservationLevel "enable"
    set rt::reportTiming false
    rt::set_parameter elaborateOnly true
    rt::set_parameter elaborateRtl true
    rt::set_parameter eliminateRedundantBitOperator false
    rt::set_parameter elaborateRtlOnlyFlow false
    rt::set_parameter writeBlackboxInterface true
    rt::set_parameter merge_flipflops true
    rt::set_parameter srlDepthThreshold 3
    rt::set_parameter rstSrlDepthThreshold 4
# MODE: 
    rt::set_parameter webTalkPath {}
    rt::set_parameter synthDebugLog false
    rt::set_parameter printModuleName false
    rt::set_parameter enableSplitFlowPath "D:/HustProjects/Project_Of_HardwareSystem_2022/2022秋硬件综合训练课设资料发布包/cpu21-riscv/Verilog/cpu21-riscv/Single_cycle_CPU/mips_cpu/mips_cpu.runs/synth_1/.Xil/Vivado-15084-ysjmachine/"
    set ok_to_delete_rt_tmp true 
    if { [rt::get_parameter parallelDebug] } { 
       set ok_to_delete_rt_tmp false 
    } 
    if {$rt::useElabCache == false} {
        set oldMIITMVal [rt::get_parameter maxInputIncreaseToMerge]; rt::set_parameter maxInputIncreaseToMerge 1000
        set oldCDPCRL [rt::get_parameter createDfgPartConstrRecurLimit]; rt::set_parameter createDfgPartConstrRecurLimit 1
        $rt::db readXRFFile
      rt::run_rtlelab -module $rt::top
        rt::set_parameter maxInputIncreaseToMerge $oldMIITMVal
        rt::set_parameter createDfgPartConstrRecurLimit $oldCDPCRL
    }

    set rt::flowresult [ source $::env(SYNTH_COMMON)/flow.tcl ]
    rt::HARTNDb_stopJobStats
    if { $rt::flowresult == 1 } { return -code error }


    if { [ info exists ::env(RT_TMP) ] } {
      if { [info exists ok_to_delete_rt_tmp] && $ok_to_delete_rt_tmp } { 
        file delete -force $::env(RT_TMP)
      }
    }

    source $::env(HRT_TCL_PATH)/rtSynthCleanup.tcl
  } ; #end uplevel
} rt::result]

if { $rt::rc } {
  $rt::db resetHdlParse
  set hsKey [rt::get_parameter helper_shm_key] 
  if { $hsKey != "" && [info exists ::env(BUILTIN_SYNTH)] && [rt::get_parameter enableParallelHelperSpawn] } { 
     $rt::db killSynthHelper $hsKey
  } 
  source $::env(HRT_TCL_PATH)/rtSynthCleanup.tcl
  return -code "error" $rt::result
}
