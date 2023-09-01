#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

#define DEVICE_NAME "led4412"
#define CLASS_NAME "chardev"

static int majorNumber;

static struct class *charClass = NULL;



static struct file_operations fops = {
    .owner = THIS_MODULE,
};

static int __init led_init(void)
{       
    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    if (majorNumber < 0) {
        printk(KERN_ALERT "Failed to register a major number\n");
        return majorNumber;
    }

    charClass = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(charClass)) {
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(charClass);
    }


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
MODULE_AUTHOR("wuwt");
MODULE_DESCRIPTION("A simple led driver for test.");
MODULE_VERSION("0.1");



