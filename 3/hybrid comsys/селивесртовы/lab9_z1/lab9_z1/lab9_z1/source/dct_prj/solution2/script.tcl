############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project dct_prj
set_top dct
add_files dct.c
add_files -tb out.golden.dat
add_files -tb in.dat
add_files -tb dct_test.c
open_solution "solution2"
set_part {xc7k160tfbg484-1}
create_clock -period 6 -name default
set_clock_uncertainty 1.25
source "./dct_prj/solution2/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
