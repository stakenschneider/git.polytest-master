#include <linux/syscalls.h>

< ... >

DECLARE_KHOOK(sys_chdir);
long khook_sys_chdir(const char __user *filename)
{
	KHOOK_USAGE_INC(sys_chdir);

	long result = KHOOK_ORIGIN(sys_chdir, filename);
	printk("Syscall 'sys_chdir' hooked. Arguments: %s. Result: %d.\n", filename, result);

	KHOOK_USAGE_DEC(sys_chdir);

	return result;
}

< ... >
