// fs/open.c

void set_fs_pwd(struct fs_struct *fs, const struct path *path)
{
	struct path old_pwd;

	path_get(path);
	spin_lock(&fs->lock);
	write_seqcount_begin(&fs->seq);
	old_pwd = fs->pwd;
	fs->pwd = *path;
	write_seqcount_end(&fs->seq);
	spin_unlock(&fs->lock);

	if (old_pwd.dentry)
		path_put(&old_pwd);
}
