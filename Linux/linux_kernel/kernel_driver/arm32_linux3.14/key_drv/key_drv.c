#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/fs.h>


#define CHRDEV_NAME "key_drv"
#define CLS_NAME "key_cls"
#define DEV_NAME "key0"

struct key_desc {
    unsigned int dev_major;
    struct class *cls;
    struct device *dev;
};
struct key_desc *key_dev;


int key_drv_open (struct inode *inode, struct file *filp) {

}


const struct file_operations key_fops = {
    .open = key_drv_open,
};



static int __init key_drv_init(void) {
    int ret;

    key_dev = kzalloc(sizeof(struct key_desc), GFP_KERNEL);
    if (!key_dev) {
        return -ENOMEM;
    }
    key_dev->dev_major = register_chrdev(key_dev->dev_major, CHRDEV_NAME, &key_fops);
    if (key_dev->dev_major < 0) {
        ret = key_dev->dev_major;
        goto err_register_chrdev;
    }
    key_dev->cls = class_create(THIS_MODULE, CLS_NAME);
    if (IS_ERR(key_dev->cls)) {
        ret = PTR_ERR(key_dev->cls);
        goto err_class_create;
    }
    key_dev->dev = device_create(key_dev->cls, NULL, MKDEV(key_dev->dev_major, 0), NULL, DEV_NAME);
    if (IS_ERR(key_dev->dev)) {
        ret = PTR_ERR(key_dev->dev);
        goto err_device_create;
    }

err_device_create:
    class_destroy(key_dev->cls);

err_class_create:
    unregister_chrdev(key_dev->dev_major, CHRDEV_NAME);

err_register_chrdev:
    kfree(key_dev);
    return ret;


}

static void __exit key_drv_exit(void) {

}


module_init(key_drv_init);
module_exit(key_drv_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("wuwt");
MODULE_DESCRIPTION("Drive for key");
MODULE_VERSION("0.1");
