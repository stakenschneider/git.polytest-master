#include <linux/syscalls.h>

< ... >

DECLARE_KHOOK(sys_sysinfo);
long khook_sys_sysinfo(struct sysinfo __user *info)
{
	KHOOK_USAGE_INC(sys_sysinfo);

	long result = KHOOK_ORIGIN(sys_sysinfo, info);
	printk("Syscall 'sys_sysinfo' hooked. Arguments: %ld, %ld, %ld, %d. Result: %d.\n",
		info->uptime, info->totalram, info->freeram, info->procs, result);

	KHOOK_USAGE_DEC(sys_sysinfo);

	return result;
}

< ... >
