############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project lab6_1
set_top foo
add_files ../../../../Desktop/SPBGPU_Mag/Antonov/lab_6/lab6_z1/lab6_1_main.c
add_files -tb ../../../../Desktop/SPBGPU_Mag/Antonov/lab_6/lab6_z1/lab6_1_test.c -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution2"
set_part {xa7a12t-csg325-1Q}
create_clock -period 6 -name default
config_export -format ip_catalog -rtl verilog
set_clock_uncertainty 0.1
source "./lab6_1/solution2/directives.tcl"
csim_design
csynth_design
cosim_design -trace_level all
export_design -rtl verilog -format ip_catalog
