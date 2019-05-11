// kernel/pid.c

pid_t __task_pid_nr_ns(struct task_struct *task, enum pid_type type,
			struct pid_namespace *ns)
{
	pid_t nr = 0;

	rcu_read_lock();
	if (!ns)
		ns = task_active_pid_ns(current);
	if (likely(pid_alive(task))) {
		if (type != PIDTYPE_PID) {
			if (type == __PIDTYPE_TGID)
				type = PIDTYPE_PID;

			task = task->group_leader;
		}
		nr = pid_nr_ns(rcu_dereference(task->pids[type].pid), ns);
	}
	rcu_read_unlock();

	return nr;
}
