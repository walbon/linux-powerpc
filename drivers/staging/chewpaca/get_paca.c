#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Walbon");
MODULE_DESCRIPTION("A simple kernel module to validate new_get_paca()");

void new_get_paca(long *ptr) {

        preempt_disable();

        __asm__ __volatile__(
        "mfspr %0,13"
        : "=r" (ptr) );

        preempt_enable();

}

static int __init get_paca_init(void)
{
        long *pptr;
        register struct paca_struct *local_paca asm("r13");

        printk(KERN_INFO "Hello world!\n");

        printk(KERN_WARNING "Paca register: %p\n", local_paca);

        new_get_paca(pptr);
        printk(KERN_WARNING "Address pptr %p\n", pptr);

        return 0;    // Non-zero return means that the module couldn't be
}
static int __init get_paca_init(void)
{
	printk(KERN_INFO "Hello world!\n");
        long ptr;
        new_get_paca(&ptr);
	printk(KERN_WARNING "Works %p\n", &ptr);
	printk(KERN_WARNING "Content: %lx\n", ptr);
	return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void __exit get_paca_cleanup(void)
{
    printk(KERN_INFO "Cleaning up module.\n");
}

module_init(get_paca_init);
module_exit(get_paca_cleanup);
