// kernel/pid.c

struct pid *alloc_pid(struct pid_namespace *ns)
{
    < ... >

    pid = kmem_cache_alloc(ns->pid_cachep, GFP_KERNEL);
    if (!pid)
        return ERR_PTR(retval);

    tmp = ns;
	pid->level = ns->level;

	for (i = ns->level; i >= 0; i--) {
		int pid_min = 1;

		idr_preload(GFP_KERNEL);
		spin_lock_irq(&pidmap_lock);

		/*
		 * init really needs pid 1, but after reaching the maximum
		 * wrap back to RESERVED_PIDS
		 */
		if (idr_get_cursor(&tmp->idr) > RESERVED_PIDS)
			pid_min = RESERVED_PIDS;

		/*
		 * Store a null pointer so find_pid_ns does not find
		 * a partially initialized PID (see below).
		 */
		nr = idr_alloc_cyclic(&tmp->idr, NULL, pid_min,
				      pid_max, GFP_ATOMIC);
		spin_unlock_irq(&pidmap_lock);
		idr_preload_end();

		if (nr < 0) {
			retval = nr;
			goto out_free;
		}

		pid->numbers[i].nr = nr;
		pid->numbers[i].ns = tmp;
		tmp = tmp->parent;
	}

    < ... >
}
