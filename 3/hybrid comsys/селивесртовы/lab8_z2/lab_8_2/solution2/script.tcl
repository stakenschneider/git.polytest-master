############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project lab_8_1
set_top foo_b
add_files ../../../../Desktop/SPBGPU_Mag/Antonov/lab8_1/foo_b.h
add_files -tb ../../../../Desktop/SPBGPU_Mag/Antonov/lab8_1/lab8_11t.h
open_solution "solution1"
set_part {xa7a12t-csg325-1Q} -tool vivado
create_clock -period 10 -name default
set_clock_uncertainty 0.1
#source "./lab_8_1/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
