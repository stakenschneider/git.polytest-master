# ==============================================================
# File generated on Sun May 05 14:49:08 +0300 2019
# Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
# SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
# IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
# Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
# ==============================================================
add_files -tb ../lab11_z2_test.c -cflags { -Wno-unknown-pragmas}
add_files lab11_z2/foo.c
set_part xa7a12tcsg325-1q
create_clock -name default -period 10
set_clock_uncertainty 0.1 default
