#include <linux/kernel.h>
#include <linux/module.h>

#include "khook/engine.c"

////////////////////////////////////////////////////////////////////////////////
// An example of using KHOOK
////////////////////////////////////////////////////////////////////////////////

#include <linux/resource.h>


KHOOK_EXT(int, sys_chmod, const char *, mode_t);
static int khook_sys_chmod(const char *pathname, mode_t mode)
{
	pr_info("chmod_syscall hooked by masha\n");
    return KHOOK_ORIGIN(sys_chmod, pathname, mode);
}

KHOOK_EXT(int, sys_chown, const char *, uid_t, gid_t);
static int khook_sys_chown(const char *pathname, uid_t owner, gid_t group)
{
	pr_info("chown_syscall hooked by masha\n");
    return KHOOK_ORIGIN(sys_chown, pathname, owner, group);
}

int init_module(void)
{	
	pr_info("module loaded by masha\n");
	return khook_init();
}

void cleanup_module(void)
{
	pr_info("module unloaded by masha\n");
	khook_cleanup();
}

MODULE_LICENSE("GPL\0but who really cares?");
