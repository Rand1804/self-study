#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/compiler.h>
#include <linux/io.h>


#define DEVICE_NAME "led4412"
#define CLASS_NAME "chardev"

#define GPL2CON 0x11000100
#define GPL2_SIZE 8

static int majorNumber;


static struct class *charClass = NULL;
static struct device *charDevice = NULL;
static void __iomem *gpl2conf = NULL;


static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = led_open,
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
    charDevice = device_create(charClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    if (IS_ERR(charDevice)) {
        class_destroy(charClass);
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device\n");
        return PTR_ERR(charDevice);
    }

    gpl2conf = ioremap(GPL2CON, GPL2_SIZE);
    if (gpl2conf == NULL) {
        printk(KERN_ALERT "Failed to map gpl2con\n");
        return -1;
    }
    gpl2dat = gpl2conf + 4;
    printk(KERN_INFO "led4412:device class created correctly\n");
    return 0;
}

static void __exit led_exit(void)
{
    device_destroy(charClass, MKDEV(majorNumber, 0));
    class_unregister(charClass);
    class_destroy(charClass);
    unregister_chrdev(majorNumber, DEVICE_NAME);
    printk(KERN_INFO "led4412: Goodbye from the LKM!\n");
}

static int led_open(struct inode *inodep, struct file *filep) {
    printk(KERN_INFO "led4412: Device has been opened\n");
    return 0;
}



module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("wuwt");
MODULE_DESCRIPTION("A simple led driver for test.");
MODULE_VERSION("0.1");



