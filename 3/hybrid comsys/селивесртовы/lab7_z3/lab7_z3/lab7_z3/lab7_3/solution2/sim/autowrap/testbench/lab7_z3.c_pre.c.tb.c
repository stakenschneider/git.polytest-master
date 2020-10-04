// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
# 1 "D:/Program_Files/projects/hls/lab7_z3/source/lab7_z3.c"
# 1 "D:/Program_Files/projects/hls/lab7_z3/source/lab7_z3.c" 1
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 147 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "D:/Program_Files/projects/hls/lab7_z3/source/lab7_z3.c" 2
void foo (int in1, int in2, int *out_data) {
 int i;
 static int accum = 0;
 L1: for(i = 0; i < 10; i++) {
  accum = accum + in1 + in2;
 }
 *out_data = accum;
}
