#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/compiler.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/slab.h>


#define GPL2CON 0x11000100
#define GPL2_SIZE 8

struct led_desc {
    int dev_major;
    struct class *cls;
    struct device *dev;
    void __iomem *reg_virt_base;
};

static struct led_desc *led_dev;

static int led_open(struct inode *inodep, struct file *filep);
static ssize_t led_write(struct file *filep, const char __user *buffer, size_t len, loff_t *offset);

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .write = led_write,
};

static int __init led_init(void)
{   
    int ret;
    u32 val;

    //Get Free Pages
    led_dev = kzalloc(sizeof(struct led_desc), GFP_KERNEL);
    if (!led_dev) {
        printk(KERN_ERR "Failed to alloc memory\n");
        return -ENOMEM;
    }
    
    led_dev->dev_major = register_chrdev(0, "led_dev", &fops);
    if (led_dev->dev_major < 0) {
        printk(KERN_ERR "Failed to register a major number\n");
        ret = led_dev->dev_major;
        goto err_register_chrdev;
    }

    led_dev->cls = class_create(THIS_MODULE, "led_cls");
    if (IS_ERR(led_dev->cls)) {        
        printk(KERN_ALERT "Failed to register device class\n");
        ret = PTR_ERR(led_dev->cls);
        goto err_class_create;
    }
    led_dev->dev = device_create(led_dev->cls, NULL, MKDEV(led_dev->dev_major, 0), NULL, "led%d", 0);
    if (IS_ERR(led_dev->dev)) {
        printk(KERN_ALERT "Failed to create the device\n");
        ret = PTR_ERR(led_dev->dev);
        goto err_device_create;
    }

    led_dev->reg_virt_base = ioremap(GPL2CON, GPL2_SIZE);
    if (!led_dev->reg_virt_base) {
        printk(KERN_ERR "Failed to ioremap\n");
        ret = -ENOMEM;
        goto err_ioremap;
    }

    val = readl(led_dev->reg_virt_base);
    val &= ~(0xf << 28);
    val |= (0x1 << 28);
    writel(val, led_dev->reg_virt_base);
    
    printk(KERN_INFO "led4412:device init success\n");
    return 0;


err_ioremap:
    device_destroy(led_dev->cls, MKDEV(led_dev->dev_major,0));
err_device_create:
    class_destroy(led_dev->cls);
err_class_create:
    unregister_chrdev(led_dev->dev_major, "led_dev");
err_register_chrdev:
    kfree(led_dev);
    return ret;
}


static void __exit led_exit(void)
{
    device_destroy(led_dev->cls, MKDEV(led_dev->dev_major, 0));
    class_destroy(led_dev->cls);
    unregister_chrdev(led_dev->dev_major, "led_dev");
    kfree(led_dev);
    printk(KERN_INFO "led4412: Goodbye from the LKM!\n");
}

static int led_open(struct inode *inodep, struct file *filep) {
    printk(KERN_INFO "led4412: Device has been opened\n");
    return 0;
}


static ssize_t led_write(struct file *filep, const char __user *buffer, size_t len, loff_t *offset) {
    int ret, val;

    ret = copy_from_user(&val, buffer, len);
    if (ret) {
        printk("Failed to copy from user\n");
        return -EFAULT;
    }

    if (val) {
        writel(readl(led_dev->reg_virt_base+4) | (0x1<<7), led_dev->reg_virt_base + 4);
    } else {
        writel(readl(led_dev->reg_virt_base+4) & ~(0x1<<7), led_dev->reg_virt_base + 4);
    }

    return 0;
}


module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("wuwt");
MODULE_DESCRIPTION("A simple led driver for test.");
MODULE_VERSION("0.1");



