/*
 * File         : timer.c
 * Author       : Sudharshan <sudharshan.pathi@gmail.com>
 * Description  : This is a simple kernel module to demonstrate
 *                usage of timers in the kernel.
 *                In this example, we are firing the timer for every
 *                200ms and on each firing, timer_callback function
 *                will execute
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>

static struct timer_list timer;

void timer_callback(struct timer_list *t)
{
    int ret;
    pr_err("In timer call back function %s jiffies  = %d\n", __func__, jiffies_to_msecs(jiffies));
    ret = mod_timer(&timer, jiffies + msecs_to_jiffies(200));
    if (ret) {
        pr_err("%s : Error in firing the timer\n", __func__);
    }
    return;
}

static int __init start_init(void)
{
    int ret;

    pr_debug("timer init function\n");
    timer_setup(&timer, timer_callback, 0);
    pr_info(" Firing the timer for 200 ms jiffies now %ld\n",jiffies);
    ret = mod_timer(&timer, jiffies + msecs_to_jiffies(200));
    if (ret) {
        pr_err("Error in firing the timer\n");
        ret = del_timer(&timer);
    }

    return 0;
}

static void __exit stop_timer(void)
{
    int ret;

    ret = del_timer(&timer);
    if (ret) {
        pr_err("The timer is still in use\n");
    }
    pr_debug("Removing the timer module\n");

    return;
}

module_init(start_init);
module_exit(stop_timer);
MODULE_AUTHOR("Sudharshan Pathi <sudharshan.pathi@gmail.com>");
MODULE_LICENSE("GPL");
