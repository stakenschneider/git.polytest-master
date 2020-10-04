############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project lab2_1
set_top lab1_1
add_files source/lab3_1.c
add_files -tb source/lab3_1_test.c -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution2"
set_part {xa7a12t-csg325-1Q}
create_clock -period 6 -name default
set_clock_uncertainty 0.1
#source "./lab2_1/solution2/directives.tcl"
csim_design
csynth_design
cosim_design -trace_level all
export_design -format ip_catalog
