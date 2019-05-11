#include <linux/syscalls.h>

< ... >

DECLARE_KHOOK(sys_getpid);
long khook_sys_getpid()
{
	KHOOK_USAGE_INC(sys_getpid);

	long result = KHOOK_ORIGIN(sys_getpid);
	printk("Syscall 'sys_getpid' hooked. Result: %d.\n", result) ;

	KHOOK_USAGE_DEC(sys_getpid);

	return result;
}

< ... >
