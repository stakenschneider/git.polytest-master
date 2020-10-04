#include <stdio.h>

int main(){

	int in1[10][10];
	int in2[10][10];

	int out[10][10];
	int exp_out[10][10];

	int i, j;

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			in1[i][j] = i + j;
			in2[i][j] = i * 10;
			out[i][j] = 0;
			exp_out[i][j] = in1[i][j] + in2[i][j];
		}
	}

	foo(in1,in2,out);

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			printf("%d + %d == Out %d == Exp %d\n", in1[i][j],in2[i][j],out[i][j], exp_out[i][j]);
			if (out[i][j] != exp_out[i][j]) {
				printf("-------ERROR-------\n");
				return -1;
			}
		}
	}
	printf("-------Test Pass-------\n");
	return 0;
}
