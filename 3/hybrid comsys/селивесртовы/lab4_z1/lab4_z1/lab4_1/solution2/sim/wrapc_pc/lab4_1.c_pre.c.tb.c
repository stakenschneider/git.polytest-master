// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
# 1 "C:/Users/Yaroslav/Desktop/SPBGPU_Mag/Antonov/plis/lectask/lab4_z1/source/lab4_1.c"
# 1 "C:/Users/Yaroslav/Desktop/SPBGPU_Mag/Antonov/plis/lectask/lab4_z1/source/lab4_1.c" 1
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 147 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Users/Yaroslav/Desktop/SPBGPU_Mag/Antonov/plis/lectask/lab4_z1/source/lab4_1.c" 2
int lab4_1( int a, int b, int *c, int *d, int *p_y) {
    int y;
    y = a*b + (*c);
    *p_y = a*b + (*d);
    return y;
}
