ROOTFS_DIR = /opt/4412/rootfs
ARCH = arm
CROSS_COMPILE = /home/wuwt/software/gcc-linaro-4.9-2016.02-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
CC = $(CROSS_COMPILE)gcc

MODULE_NAME1 = plat_led_pdev
MODULE_NAME2 = plat_led_pdrv
APP_NAME = led_test

ifeq ($(KERNELRELEASE), )
KERNEL_DIR = /home/wuwt/code/linux-3.14
CUR_DIR = $(shell pwd)

all:
# C=2 CHECK="/usr/bin/sparse"
	make -C $(KERNEL_DIR) M=$(CUR_DIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
	$(CC) $(APP_NAME).c -o $(APP_NAME)
clean:
	make -C $(KERNEL_DIR) M=$(CUR_DIR) clean
	rm -rf $(APP_NAME)
install:
	cp -raf *.ko $(APP_NAME) $(ROOTFS_DIR)/drv_module
	
else
obj-m += $(MODULE_NAME1).o
obj-m += $(MODULE_NAME2).o
# obj-m += math.o

endif