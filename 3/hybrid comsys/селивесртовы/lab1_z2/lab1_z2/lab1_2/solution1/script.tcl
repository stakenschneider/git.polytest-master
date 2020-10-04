############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project lab1_2
set_top lab1_2
add_files ../../../../Desktop/SPBGPU_Mag/Antonov/lab_1/lab1_2.c
add_files -tb ../../../../Desktop/SPBGPU_Mag/Antonov/lab_1/lab1_2_test.c -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1"
set_part {xa7a12t-csg325-1Q} -tool vivado
create_clock -period 6 -name default
set_clock_uncertainty 0.1
#source "./lab1_2/solution1/directives.tcl"
csim_design
csynth_design
cosim_design -trace_level all
export_design -format ip_catalog
