#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main()
{
	printf("Invoking 'exit()' system call\n");
	syscall(60);
	printf("Message after exit call\n");
}