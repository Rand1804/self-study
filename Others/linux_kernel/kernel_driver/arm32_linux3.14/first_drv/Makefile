ROOTFS_DIR = /opt/4412/rootfs
ARCH = arm
CROSS_COMPILE = /home/wuwt/software/gcc-linaro-4.9-2016.02-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-


ifeq ($(KERNELRELEASE), )
KERNEL_DIR = /home/wuwt/code/linux-3.14
CUR_DIR = $(shell pwd)

all:
# C=2 CHECK="/usr/bin/sparse"
	make -C $(KERNEL_DIR) M=$(CUR_DIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
clean:
	make -C $(KERNEL_DIR) M=$(CUR_DIR) clean
install:
	cp -raf *.ko $(ROOTFS_DIR)/drv_module
	
else
obj-m += led4412.o
# obj-m += math.o

endif