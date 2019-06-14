#include <linux/kernel.h>
#include <linux/module.h>

#include "khook/engine.c"

////////////////////////////////////////////////////////////////////////////////
// An example of using KHOOK
////////////////////////////////////////////////////////////////////////////////

#include <linux/resource.h>


KHOOK_EXT(int, sys_getpriority, int, int);
static int khook_sys_getpriority(int which, int who)
{
	pr_info("getpriority hooked by mikhailme\n");
        return KHOOK_ORIGIN(sys_getpriority, which, who);
 
}


KHOOK_EXT(int, sys_setpriority, int, int, int);
static int khook_sys_setpriority(int which, int who, int niceval)
{
	pr_info("setpriority hooked by mikhailme\n");
        return KHOOK_ORIGIN(sys_setpriority, which, who, niceval);
}

int init_module(void)
{	
	pr_info("module loaded\n");
	return khook_init();
}

void cleanup_module(void)
{
	pr_info("module unloaded\n");
	khook_cleanup();
}


MODULE_LICENSE("GPL\0but who really cares?");
