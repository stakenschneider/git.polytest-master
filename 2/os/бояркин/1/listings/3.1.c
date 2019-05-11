// fs/open.c

int ksys_chdir(const char __user *filename)
{
	struct path path;
	int error;
	unsigned int lookup_flags = LOOKUP_FOLLOW | LOOKUP_DIRECTORY;
retry:
	error = user_path_at(AT_FDCWD, filename, lookup_flags, &path);
	if (error)
		goto out;

	error = inode_permission(path.dentry->d_inode, MAY_EXEC | MAY_CHDIR);
	if (error)
		goto dput_and_out;

	set_fs_pwd(current->fs, &path);

dput_and_out:
	path_put(&path);
	if (retry_estale(error, lookup_flags)) {
		lookup_flags |= LOOKUP_REVAL;
		goto retry;
	}
out:
	return error;
}
