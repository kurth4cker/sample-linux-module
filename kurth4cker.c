#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("I'm pörfek hacker men.");

int kurth4cker_init(void);
void kurth4cker_exit(void);

int kurth4cker_init(void) {
	printk(KERN_INFO "hello world\n");

	return 0;
}

void kurth4cker_exit(void) {
	printk(KERN_INFO "goodbye world\n");
}

module_init(kurth4cker_init);
module_exit(kurth4cker_exit);
