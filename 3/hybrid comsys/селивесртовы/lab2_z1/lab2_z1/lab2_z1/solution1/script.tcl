############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project lab2_1
set_top lab1_1
add_files ../../../../Desktop/SPBGPU_Mag/Antonov/lab_2/lab2_z1/source/lab2_1.c
add_files -tb ../../../../Desktop/SPBGPU_Mag/Antonov/lab_2/lab2_z1/source/lab2_1_test.c
open_solution "solution1"
set_part {xa7a12tcsg325-1Q} -tool vivado
create_clock -period 6 -name default
config_export -format ip_catalog -rtl verilog
set_clock_uncertainty 0.1
#source "./lab2_1/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog
