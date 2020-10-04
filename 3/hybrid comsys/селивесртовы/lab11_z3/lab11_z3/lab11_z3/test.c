#define N 16
#include <stdio.h>
int main()

{
	int d_in[N],d_actual[N],d_expected[N];
	int passed = 1;
	int i;
	for(i = 0;i < N;i++)
	{
		d_in[i] = i;
		d_expected[i] = i * i;
	}

	foo(d_in,d_actual);

	for(i = 0; i < N; i++)
	{
		printf("Expected [%d] actual [%d]\n",d_expected[i], d_actual[i]);
		if(d_expected[i] != d_actual[i])
		{
			passed = 1;
		}
	}
	if(passed != 1){
		printf("----------Test failed----------\n");
	} else {
		printf("----------Test passed----------\n");
	}
}
