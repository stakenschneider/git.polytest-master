#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

int main()
{
	int p1 = getpriority(PRIO_PROCESS, 0);
	printf("priority before change :%d\n", p1);

  	setpriority(PRIO_PROCESS, 0, 3);
	int p2 = getpriority(PRIO_PROCESS, 0);
	printf("changed priority to :%d\n", p2);
	
	return 0;
}
