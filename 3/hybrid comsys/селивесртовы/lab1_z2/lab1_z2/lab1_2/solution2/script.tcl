############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project lab1_2
set_top lab1_2
add_files ../../../../Desktop/SPBGPU_Mag/Antonov/lab_1/lab1_2.c
add_files -tb ../../../../Desktop/SPBGPU_Mag/Antonov/lab_1/lab1_2_test.c -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution2"
set_part {xa7a12t-csg325-1Q}
create_clock -period 10 -name default
config_export -format ip_catalog -rtl verilog
set_clock_uncertainty 0.1
#source "./lab1_2/solution2/directives.tcl"
csim_design
csynth_design
cosim_design -trace_level all
export_design -rtl verilog -format ip_catalog
