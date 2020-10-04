
#include <stdio.h>
int main()
{
	//Init
	int a_actual[N],a_expected[N],b[N],c[N];
	int passed = 1;
	int i;
	for(i = 0; i < N; i++)
	{
		b[i] = i;
		c[i] = i * i * 3;
		a_expected[i] = b[i] + c[i];
	}
	//Call function
	foo(a_actual,b,c);
	//Check
	for(i = 0; i < N;i++)
	{
		printf("Expected [%d] actual [%d]\n",a_expected[i],a_actual[i]);
		if(a_expected[i] != a_actual[i])
		{
			passed = -1;
		}
	}

	if(passed != 1) {
		printf("-----------Test failed--------------\n");
	} else {
		printf("-----------Test passed--------------\n");
	}
}
