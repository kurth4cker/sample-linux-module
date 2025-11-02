#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>

#include "kurth4cker.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("I'm pörfek hacker men.");

static int kurth4cker_init(void);
static void kurth4cker_exit(void);
static int kurth4cker_open(struct inode *inodep, struct file *filp);
static int kurth4cker_release(struct inode *inodep, struct file *filp);
static ssize_t kurth4cker_read(struct file *filp, char *buf, size_t size, loff_t *off);
static ssize_t kurth4cker_write(struct file *filp, const char *buf, size_t size, loff_t *off);
static long kurth4cker_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);

module_init(kurth4cker_init);
module_exit(kurth4cker_exit);

static void walk_process_threads(void);
// static void walk_processes(void);
static long ioctl_test(struct file *filp, unsigned long arg);

static dev_t dev;
static struct cdev cdev;
static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = kurth4cker_open,
	.release = kurth4cker_release,
	.read = kurth4cker_read,
	.write = kurth4cker_write,
	.unlocked_ioctl = kurth4cker_ioctl,
};

static int kurth4cker_init(void) {
	printk(KERN_INFO "kurth4cker: initializing...\n");

	int result;
	if ((result = alloc_chrdev_region(&dev, 0, 1, "kurth4cker")) < 0) {
		printk(KERN_ERR "kurth4cker: cannot alloc char drivers\n");
		return result;
	}
	cdev_init(&cdev, &fops);
	if ((result = cdev_add(&cdev, dev, 1)) < 0) {
		unregister_chrdev_region(dev, 1);
		printk(KERN_ERR "kurth4cker: cannot add device\n");
		return result;
	}

	printk(KERN_INFO "kurth4cker: initialized\n");

	return 0;
}

static void kurth4cker_exit(void) {
	cdev_del(&cdev);
	unregister_chrdev_region(dev, 1);

	printk(KERN_INFO "kurth4cker: exit\n");
}
static int kurth4cker_open(struct inode *inodep, struct file *filp) {
	printk(KERN_INFO "kurth4cer: opened\n");

	return 0;
}

static int kurth4cker_release(struct inode *inodep, struct file *filp) {
	printk(KERN_INFO "kurth4cer: closed\n");

	return 0;
}

static ssize_t kurth4cker_read(struct file *filp, char *buf, size_t size, loff_t *off) {
	printk(KERN_INFO "kurth4cer: read\n");

	return 0;
}

static ssize_t kurth4cker_write(struct file *filp, const char *buf, size_t size, loff_t *off) {
	printk(KERN_INFO "kurth4cer: wrote\n");
	return 0;
}

static long kurth4cker_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
	printk(KERN_INFO "kurth4cer: ioctl\n");

	long result;
	switch (cmd) {
	case IOC_KURTH4CKER:
		result = ioctl_test(filp, arg);
		break;
	default:
		result = -ENOTTY;
	}

	return result;
}

static long ioctl_test(struct file *filp, unsigned long arg) {
	walk_process_threads();

	return 0;
}

static void walk_process_threads(void) {
	struct task_struct *ts;

	rcu_read_lock();

	for_each_thread(current, ts) {
		printk(KERN_INFO "kurth4cker: Thread PID = %d, COMM = %s\n", ts->pid, ts->comm);
	}

	rcu_read_unlock();
}

// static void walk_processes(void) {
// 	struct task_struct *ts;

// 	rcu_read_lock();

// 	for_each_process(ts) {
// 		printk(KERN_INFO "kurth4cker: PID = %d, COMM = %s", ts->pid, ts->comm);
// 	}

// 	rcu_read_unlock();
// }
