void foo (int in1[10][10], int in2[10][10], int out[10][10]) {
	int i, j;
	L1:for (i = 0; i < 10; i++) {
		L2:for (j = 0; j < 10; j++) {
			out[i][j] = in1[i][j] + in2[i][j];
		}
	}
}
