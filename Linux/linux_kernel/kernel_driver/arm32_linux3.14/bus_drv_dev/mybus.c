#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>


int mybus_match(struct device *dev, struct device_driver *drv)
{
	if(!strncmp(drv->name, dev->kobj.name, strlen(drv->name)))
	{
		printk("match ok\n");
		return 1;
	}else{
		printk("match failed\n");
		return 0;

	}

	return 0;
}


struct bus_type mybus = {
	.name = "mybus",
	.match = mybus_match,
};

EXPORT_SYMBOL(mybus);


static int __init mybus_init(void)
{
	printk("----------%s-------------\n", __FUNCTION__);
	int ret;

	// /sys/bus/mybus
	ret = bus_register(&mybus);
	if(ret != 0)
	{
		printk("bus_register error\n");
		return ret;
	}

	
	return 0;
}

static void __exit mybus_exit(void)
{
	printk("----------%s-------------\n", __FUNCTION__);
	bus_unregister(&mybus);
	
}

module_init(mybus_init);
module_exit(mybus_exit);
MODULE_LICENSE("GPL");

