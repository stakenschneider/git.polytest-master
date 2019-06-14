#define _GNU_SOURCE 
#include <unistd.h>
#include <sys/syscall.h> 
#include <stdio.h>

main() {
	long t = syscall(SYS_time);
	printf("Time in seconds %ld \n", t);
}
