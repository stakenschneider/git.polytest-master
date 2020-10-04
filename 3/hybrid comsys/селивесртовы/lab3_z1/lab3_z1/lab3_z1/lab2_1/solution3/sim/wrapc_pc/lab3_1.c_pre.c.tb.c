// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
# 1 "D:/Program_Files/projects/hls/lab3_z1/source/lab3_1.c"
# 1 "D:/Program_Files/projects/hls/lab3_z1/source/lab3_1.c" 1
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 147 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "D:/Program_Files/projects/hls/lab3_z1/source/lab3_1.c" 2
int lab1_1( char a, char b, char c, char d) {
#pragma HLS INTERFACE ap_ctrl_none port=return
int y;
y = a*b+c+d;
return y;
}
