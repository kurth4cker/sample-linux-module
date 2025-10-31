#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("I'm pörfek hacker men.");

static void walk_processes(void) {
	struct task_struct *ts;
	struct list_head *lh;

	rcu_read_lock();

	lh = rcu_dereference(init_task.tasks.next);
	while (lh != &init_task.tasks) {
		ts = container_of(lh, struct task_struct, tasks);
		printk(KERN_INFO "kurth4cker: PID = %d, COMM = %s", ts->pid, ts->comm);
		lh = rcu_dereference(ts->tasks.next);
	}

	rcu_read_unlock();
}

int kurth4cker_init(void);
void kurth4cker_exit(void);

int kurth4cker_init(void) {
	printk(KERN_INFO "kurth4cker: hello world\n");

	walk_processes();

	return 0;
}

void kurth4cker_exit(void) {
	printk(KERN_INFO "kurth4cker: goodbye world\n");
}

module_init(kurth4cker_init);
module_exit(kurth4cker_exit);
