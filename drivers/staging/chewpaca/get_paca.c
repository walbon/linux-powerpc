#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include "paca.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Walbon");
MODULE_DESCRIPTION("A simple kernel module to validate new_get_paca()");

void new_get_paca(struct paca_struct *ptr) {

        preempt_disable();

        __asm__ __volatile__(
        "mr %0,13"
        :"=r" (ptr)
	);

        preempt_enable();

}

static int __init get_paca_init(void)
{
        struct paca_struct *pptr;
        register struct paca_struct *local_paca asm("r13");

        printk(KERN_INFO "Hello world!\n");

        printk(KERN_WARNING "Paca register: %p\n", local_paca);
	printk(KERN_WARNING "Paca content hw_cpu_id: %d\n",local_paca->hw_cpu_id);

        new_get_paca(pptr);
        printk(KERN_WARNING "Address pptr %p\n", pptr);
	printk(KERN_WARNING "pptr content hw_cpu_id: %d\n",pptr->hw_cpu_id);

        return 0;    // Non-zero return means that the module couldn't be
}

static void __exit get_paca_cleanup(void)
{
    printk(KERN_INFO "Cleaning up module.\n");
}

module_init(get_paca_init);
module_exit(get_paca_cleanup);
