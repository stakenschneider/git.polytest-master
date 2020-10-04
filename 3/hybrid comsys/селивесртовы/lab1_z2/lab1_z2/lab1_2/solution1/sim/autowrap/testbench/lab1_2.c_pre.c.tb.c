// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
# 1 "C:/Users/Yaroslav/Desktop/SPBGPU_Mag/Antonov/lab_1/lab1_2.c"
# 1 "C:/Users/Yaroslav/Desktop/SPBGPU_Mag/Antonov/lab_1/lab1_2.c" 1
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 147 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Users/Yaroslav/Desktop/SPBGPU_Mag/Antonov/lab_1/lab1_2.c" 2
void lab1_2 (int in[3], char a, char b, char c, int out[3]) {
int x,y;
for(int i = 0; i < 3; i++) {
x = in[i];
y = a*x + b + c;
out[i] = y;
}
}
