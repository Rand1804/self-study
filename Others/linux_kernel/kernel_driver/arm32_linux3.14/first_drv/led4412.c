#include <linux/init.h>
#include <linux/module.h>


#include "math.h"

int myval = 100;
char *mystr = "hello";

module_param(myval, int, S_IRUGO);
module_param(mystr, charp, S_IRUGO);

static int __init led_init(void)
{       
    printk("--------------%s----------------\n", __FUNCTION__);
    printk("myval=%d\n", myval);
    printk("mystr=%s\n", mystr);

    printk("a+b=%d\n", my_add(1, 2));
    return 0;
}

static void __exit led_exit(void)
{
    printk("--------------%s----------------\n", __FUNCTION__);
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");



