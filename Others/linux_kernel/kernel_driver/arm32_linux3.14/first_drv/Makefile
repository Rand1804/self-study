ROOTFS_DIR = /opt/4412/rootfs

ifeq ($(KERNELRELEASE), )
KERNEL_DIR = /home/wuwt/code/linux-3.14
CUR_DIR = $(shell pwd)

all:
	make -C $(KERNEL_DIR) M=$(CUR_DIR) modules
clean:
	make -C $(KERNEL_DIR) M=$(CUR_DIR) clean
install:
	cp -raf *.ko $(ROOTFS_DIR)/drv_module
	
else
obj-m += led4412.o
# obj-m += math.o

endif