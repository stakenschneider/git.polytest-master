#define N 16
void foo(int a[N], int b[N], int c[N])
{
	int i;
	Add:for (i = 0; i < N; i++)
	{
		a[i] = b[i] + c[i];
	}
}
