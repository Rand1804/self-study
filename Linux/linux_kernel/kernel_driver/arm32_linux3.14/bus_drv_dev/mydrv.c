#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/io.h>
#include "dev_info.h"


struct mydev_desc  *pdesc;

int mydrv_probe(struct device *dev)
{
	printk("----------%s-------------\n", __FUNCTION__);

	pdesc = (struct mydev_desc  *)dev->platform_data;

	printk("name = %s\n", pdesc->name);
	printk("irqno = %d\n", pdesc->irqno);

	unsigned long *paddr = ioremap(pdesc->addr, 8);

	// platform_bus_type
	// struct platform_device
	// struct platform_driver

	// platform_device_unregister(struct platform_device * pdev)
	
	// platform_driver_register(struct platform_driver *drv);
	// platform_driver_unregister(struct platform_driver *drv);
	
	return 0;
}

int mydrv_remove(struct device *dev)
{

	printk("----------%s-------------\n", __FUNCTION__);
	return 0;
}

extern struct bus_type mybus;

struct device_driver mydrv = {
	.name = "fsdev_drv",
	.bus = &mybus,
	.probe = mydrv_probe,
	.remove = mydrv_remove,
};


static int __init mydrv_init(void)
{
	printk("----------%s-------------\n", __FUNCTION__);
	int ret;
	ret  = driver_register(&mydrv);
	if(ret < 0)
	{
		printk("device_register error\n");
		return ret;
	}
	

	return 0;
}

static void __exit mydrv_exit(void)
{

	printk("----------%s-------------\n", __FUNCTION__);
	driver_unregister(&mydrv);
}





module_init(mydrv_init);
module_exit(mydrv_exit);
MODULE_LICENSE("GPL");

