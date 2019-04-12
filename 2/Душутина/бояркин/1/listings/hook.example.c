#include <linux/fs.h>

< ... >

DECLARE_KHOOK(inode_permission);
int khook_inode_permission(struct inode * inode, int mode)
{
	int result;

	KHOOK_USAGE_INC(inode_permission);

	debug("%s(%pK,%08x) [%s]\n", __func__, inode, mode, current->comm);

	result = KHOOK_ORIGIN(inode_permission, inode, mode);

	debug("%s(%pK,%08x) [%s] = %d\n", __func__, inode, mode, current->comm, result);

	KHOOK_USAGE_DEC(inode_permission);

	return result;
}

< ... >
