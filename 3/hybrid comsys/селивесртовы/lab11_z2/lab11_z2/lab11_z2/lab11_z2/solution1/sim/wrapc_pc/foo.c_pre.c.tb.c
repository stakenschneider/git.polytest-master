// ==============================================================
// File generated on Sun May 05 14:55:33 +0300 2019
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#1 "C:/Users/boris/OneDrive/WorkingDirectory/2018-2019/VivadoHLSLabs/spring/lab11_z2/source/lab11_z2/foo.c"
#1 "C:/Users/boris/OneDrive/WorkingDirectory/2018-2019/VivadoHLSLabs/spring/lab11_z2/source/lab11_z2/foo.c" 1
#1 "<built-in>" 1
#1 "<built-in>" 3
#147 "<built-in>" 3
#1 "<command line>" 1
#1 "<built-in>" 2
#1 "C:/Users/boris/OneDrive/WorkingDirectory/2018-2019/VivadoHLSLabs/spring/lab11_z2/source/lab11_z2/foo.c" 2
void foo(int d_in[3], int d_out[3])
{
 int i;
 int t_in,t_r;
 Loop: for(i = 0; i < 3; i++)
 {
  t_in = d_in[i];
  t_r = t_in * t_in;
  d_out[i] = t_r;
 }
}
