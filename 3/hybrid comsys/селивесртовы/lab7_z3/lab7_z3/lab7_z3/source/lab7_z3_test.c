#include <stdio.h>

int main() {
	int in1 = 4;
	int in2 = 6;
	int out = 0; int *o_p = &out;
	int exp_out = 100;
	
	foo(in1,in2,o_p);

	printf("Out %d == Exp %d\n", out, exp_out);
	if (out != exp_out) {
		fprintf(stdout, "-------ERROR-------\n");
		return -1;
	} else {
		fprintf(stdout, "-------Test Pass-------\n");
		return 0;
	}
}
