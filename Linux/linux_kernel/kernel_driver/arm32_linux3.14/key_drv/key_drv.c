#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/atomic.h>
#include <linux/io.h>
#include <linux/input.h>


#define CHRDEV_NAME "key_drv"
#define CLS_NAME "key_cls"
#define DEV_NAME "key0"
#define GPX1CON 0x11000C20

struct key_event {
    int code;
    int value;
};


struct key_desc {
    unsigned int dev_major;
    struct class *cls;
    struct device *dev;
    int irqno;
    void __iomem *reg_base;
    wait_queue_head_t r_wait;
    atomic_t ev_press;
    struct key_event ev;
};
struct key_desc *key_dev;


int key_drv_open(struct inode *inode, struct file *filp) {
    return 0;
}

ssize_t key_drv_read(struct file *filp, char __user *buf, size_t count, loff_t *fpos) {
    // implement unblock read
    if (filp->f_flags & O_NONBLOCK && !atomic_read(&key_dev->ev_press)) {
        return -EAGAIN;
    }

    wait_event_interruptible(key_dev->r_wait, atomic_read(&key_dev->ev_press));
    atomic_set(&key_dev->ev_press, 0);

    if (copy_to_user(buf, &key_dev->ev, sizeof(key_dev->ev))) {
        return -EFAULT;
    }

    return sizeof(key_dev->ev);
}


const struct file_operations key_fops = {
    .open = key_drv_open,
    .read = key_drv_read,
};



irqreturn_t key_irq_handler(int irqno, void *dev_id) {
    int reg_val;

    printk("key irq handler\n");
    reg_val = readl(key_dev->reg_base + 4) & (0x1<<2);

    if (reg_val) {
        printk("key down\n");
        key_dev->ev.code = KEY_ENTER;
        key_dev->ev.value = 1;
    } else {
        printk("key up\n");
        key_dev->ev.code = KEY_ENTER;
        key_dev->ev.value = 0;
    }

    atomic_set(&key_dev->ev_press, 1);
    wake_up_interruptible(&key_dev->r_wait);
    return IRQ_HANDLED;
}



int get_irqno_from_node(void) {
    int irqno;

    struct device_node *np = of_find_node_by_path("/key_int_node");
    if (!np) {
        return -ENODEV;
    }

    irqno = irq_of_parse_and_map(np, 0);
    if (!irqno) {
        return -EINVAL;
    }
    
    return irqno;
}


static int __init key_drv_init(void) {
    int ret;

    key_dev = kzalloc(sizeof(struct key_desc), GFP_KERNEL);
    if (!key_dev) {
        return -ENOMEM;
    }
    key_dev->dev_major = register_chrdev(0, CHRDEV_NAME, &key_fops);
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

    // register irq
    key_dev->irqno = get_irqno_from_node();
    if (key_dev->irqno < 0) {
        ret = key_dev->irqno;
        goto err_get_irqno;
    }
    ret = request_irq(key_dev->irqno, key_irq_handler, IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING, "key3_eint10", NULL);
    if (ret < 0) {
        goto err_request_irq;
    }

    key_dev->reg_base = ioremap(GPX1CON, 8);
    if (!key_dev->reg_base) {
        ret = -ENOMEM;
        goto err_ioremap;
    }

    // implement block read
    init_waitqueue_head(&key_dev->r_wait);

    return 0;

err_ioremap:
    free_irq(key_dev->irqno, NULL);

err_request_irq:
    
err_get_irqno:
    device_destroy(key_dev->cls, MKDEV(key_dev->dev_major, 0));

err_device_create:
    class_destroy(key_dev->cls);

err_class_create:
    unregister_chrdev(key_dev->dev_major, CHRDEV_NAME);

err_register_chrdev:
    kfree(key_dev);
    return ret;
}

static void __exit key_drv_exit(void) {
    iounmap(key_dev->reg_base);
    free_irq(key_dev->irqno, NULL);
    device_destroy(key_dev->cls, MKDEV(key_dev->dev_major, 0));
    class_destroy(key_dev->cls);
    unregister_chrdev(key_dev->dev_major, CHRDEV_NAME);
    kfree(key_dev);

}


module_init(key_drv_init);
module_exit(key_drv_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("wuwt");
MODULE_DESCRIPTION("Drive for key");
MODULE_VERSION("0.1");
