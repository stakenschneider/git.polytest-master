// kernel/pid.c

static int alloc_pidmap(struct pid_namespace *pid_ns)
{
    < ... >

	int i, offset, max_scan, pid, last = pid_ns->last_pid;
	struct pidmap *map;
	pid = last + 1;
	if (pid >= pid_max)
	   pid = RESERVED_PIDS;

    < ... >
}
