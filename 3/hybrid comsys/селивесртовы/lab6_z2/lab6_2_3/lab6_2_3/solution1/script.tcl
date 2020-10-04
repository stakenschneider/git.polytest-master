############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project lab6_2_3
set_top foo
add_files ../../../../Desktop/SPBGPU_Mag/Antonov/lab_6/lab6_z2_3/lab6_23main.c
add_files -tb ../../../../Desktop/SPBGPU_Mag/Antonov/lab_6/lab6_z2_3/lab6_23test.c
open_solution "solution1"
set_part {xa7a12tcsg325-1Q} -tool vivado
create_clock -period 10 -name default
set_clock_uncertainty 0.1
source "./lab6_2_3/solution1/directives.tcl"
csim_design
csynth_design
cosim_design -trace_level all
export_design -rtl verilog -format ip_catalog
