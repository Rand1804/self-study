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
    key_dev = kzalloc(sizeof(struct key_desc), GFP_KERNEL);
    key_dev->dev_major = register_chrdev(key_dev->dev_major, CHRDEV_NAME, &key_fops);
    key_dev->cls = class_create(THIS_MODULE, CLS_NAME);
    key_dev->dev = device_create(key_dev->cls, NULL, MKDEV(key_dev->dev_major, 0), NULL, DEV_NAME);


}

static void __exit key_drv_exit(void) {

}


module_init(key_drv_init);
module_exit(key_drv_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("wuwt");
MODULE_DESCRIPTION("Drive for key");
MODULE_VERSION("0.1");
