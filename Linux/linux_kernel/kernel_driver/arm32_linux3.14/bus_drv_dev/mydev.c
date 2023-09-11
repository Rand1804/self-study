#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include "dev_info.h"


extern struct bus_type mybus;



struct mydev_desc devinfo = {
	.name = "testdev",
	.irqno = 9999,
	.addr = 0x30008000,
};

void mydev_release(struct device *dev)
{

	printk("----------%s-------------\n", __FUNCTION__);
}


struct device  mydev= {
	.init_name = "fsdev_drv",
	.bus = &mybus,
	.release = mydev_release,
	.platform_data = &devinfo,
};



static int __init mydev_init(void)
{
	printk("----------%s-------------\n", __FUNCTION__);

	int ret;
	ret  = device_register(&mydev);
	if(ret < 0)
	{
		printk("device_register error\n");
		return ret;
	}
	

	return 0;
}

static void __exit mydev_exit(void)
{
	printk("----------%s-------------\n", __FUNCTION__);
	device_unregister(&mydev);
}



module_init(mydev_init);
module_exit(mydev_exit);
MODULE_LICENSE("GPL");

