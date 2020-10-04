############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project lab7_3
set_top foo
add_files source/lab7_z3.c
add_files -tb source/lab7_z3_test.c -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution3"
set_part {xa7a12t-csg325-1Q}
create_clock -period 10 -name default
set_clock_uncertainty 0.1
source "./lab7_3/solution3/directives.tcl"
csim_design
csynth_design
cosim_design -trace_level all
export_design -format ip_catalog
