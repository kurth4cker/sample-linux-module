#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("I'm pörfek hacker men.");

static void walk_processes(void) {
	struct task_struct *ts;

	rcu_read_lock();

	for_each_process(ts) {
		printk(KERN_INFO "kurth4cker: PID = %d, COMM = %s", ts->pid, ts->comm);
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
