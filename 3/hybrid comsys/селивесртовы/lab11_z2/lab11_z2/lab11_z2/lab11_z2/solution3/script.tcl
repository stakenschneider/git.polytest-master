############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project lab11_z2
set_top foo
add_files lab11_z2/foo.c
add_files -tb test.c
open_solution "solution3"
set_part {xa7a12tcsg325-1q}
create_clock -period 10 -name default
set_clock_uncertainty 0.1
#source "./lab11_z2/solution3/directives.tcl"
csim_design
csynth_design
cosim_design -trace_level all -tool xsim
export_design -format ip_catalog
