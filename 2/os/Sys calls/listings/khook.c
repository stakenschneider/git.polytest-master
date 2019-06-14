#include <linux/kernel.h>
#include <linux/module.h>

#include "khook/engine.c"

////////////////////////////////////////////////////////////////////////////////
// An example of using KHOOK
////////////////////////////////////////////////////////////////////////////////

#include <linux/resource.h>


KHOOK_EXT(long, sys_alarm, unsigned int);
static long khook_sys_alarm(unsigned int seconds)
{
	pr_info("alarm_syscall hooked by lorismelik\n");
    return KHOOK_ORIGIN(sys_alarm, seconds);
}

KHOOK_EXT(long, sys_time, time_t*);
static long khook_sys_time(time_t *tloc)
{
	pr_info("time_syscall hooked by lorismelik\n");
    return KHOOK_ORIGIN(sys_time, tloc);
}

int init_module(void)
{	
	pr_info("module loaded by lorismelik\n");
	return khook_init();
}

void cleanup_module(void)
{
	pr_info("module unloaded by lorismelik\n");
	khook_cleanup();
}

MODULE_LICENSE("GPL\0but who really cares?");
