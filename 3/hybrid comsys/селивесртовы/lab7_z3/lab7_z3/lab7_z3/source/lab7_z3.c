void foo (int in1, int in2, int *out_data) {
	int i;
	static int accum = 0;
	L1: for(i = 0; i < 10; i++) {
		accum = accum + in1 + in2;
	}
	*out_data = accum;
}
