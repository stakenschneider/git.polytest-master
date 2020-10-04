#define N 16
void foo(int d_in[N], int d_out[N])
{
	int i;
	int t_in,t_r;
	#pragma HLS LATENCY max=8
	Loop: for(i = 0; i < N; i++)
	{
		t_in = d_in[i];
		t_r = t_in * t_in;
		d_out[i] = t_r;
	}
}
