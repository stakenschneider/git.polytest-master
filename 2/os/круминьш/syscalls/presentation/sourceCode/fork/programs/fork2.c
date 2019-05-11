#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
int main()
{
	printf("Invoking 'fork()' system call\n");
	long resCode = syscall(57);
	if(resCode == 0)
		printf("I'm child process, my pid is %d\n", resCode);
	else
		printf("I'm parent process, my pid is %d\n", resCode);
}