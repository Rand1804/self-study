ROOTFS_DIR = /opt/4412/rootfs
MODULE_NAME = mybus
MODULE_NAME2 = mydev
MODULE_NAME3 = mydrv
APP_NAME = led_test

ARCH = arm
CROSS_COMPILE = /home/wuwt/software/gcc-linaro-4.9-2016.02-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
CC = $(CROSS_COMPILE)gcc


ifeq ($(KERNELRELEASE), )
KERNEL_DIR = /home/wuwt/code/linux-3.14
CUR_DIR = $(shell pwd)


all :
	make -C $(KERNEL_DIR) M=$(CUR_DIR) modules
	#$(CC) $(MODULE_NAME)_test.c -o $(MODULE_NAME)_test
clean :
	make -C $(KERNEL_DIR) M=$(CUR_DIR) clean

install:
	cp -raf *.ko   $(ROOTFS_DIR)/drv_module
	
else

obj-m += $(MODULE_NAME).o
obj-m += $(MODULE_NAME2).o
obj-m += $(MODULE_NAME3).o

endif
