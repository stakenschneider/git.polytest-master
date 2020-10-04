# 1 "D:/Program_Files/projects/hls/lab7_z2/source/lab7_z2.c"
# 1 "D:/Program_Files/projects/hls/lab7_z2/source/lab7_z2.c" 1
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 147 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "D:/Program_Files/projects/hls/lab7_z2/source/lab7_z2.c" 2
void foo (int in1[10][10], int in2[10][10], int out[10][10]) {
 int i, j;
 L1:for (i = 0; i < 10; i++) {
  L2:for (j = 0; j < 10; j++) {
   out[i][j] = in1[i][j] + in2[i][j];
  }
 }
}
