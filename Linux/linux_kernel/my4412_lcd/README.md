

1.使用tf卡移植uboot启动开发板

设置开发板为tf卡启动模式

```shell
sudo umount /dev/sdX*

# 在指定位置写入uboot
sudo dd if=u-boot.bin of=/dev/sdX bs=512 seek=1
```

2.加载内核和设备树

```shell
ext2load mmc 0:1 0x40007000 uImage
ext2load mmc 0:1 0x41000000 exynos4412-itop-elite.dtb
bootm 0x40008000 - 0x41000000



setenv bootcmd 'ext2load mmc 0:1 0x40007000 uImage; ext2load mmc 0:1 0x41000000 exynos4412-itop-elite.dtb; bootm 0x40007000 - 0x41000000'
setenv bootcmd 'fatload mmc 0:1 0x40007000 uImage-itop; fatload mmc 0:1 0x41000000 exynos4412-itop-elite.dtb; bootm 0x40007000 - 0x41000000'


# 内存根文件系统
setenv bootcmd 'ext2load mmc 0:1 0x40007000 uImage; ext2load mmc 0:1 0x42000000 rootfs.ext4; ext2load mmc 0:1 0x41000000 exynos4412-itop-elite.dtb; bootm 0x40007000 0x42000000 0x41000000'
setenv bootargs console=ttySAC2,115200n8  earlyprintk init=/linuxrc


setenv bootargs console=ttySAC2,115200 init=/linuxrc root=/dev/mmcblk3p2 rw rootwait 


setenv bootargs console=ttySAC2,115200n8  earlyprintk init=/linuxrc root=/dev/nfs rw nfsroot=192.168.0.102:/srv/nfs/rootfs rootwait 
```





new:

```c
setenv bootcmd 'fatload mmc 0:1 0x40008000 uImage; fatload mmc 0:1 0x41000000 exynos4412-fs4412.dtb; bootm 0x40008000 - 0x41000000'
setenv bootargs console=ttySAC2,115200 init=/linuxrc root=/dev/mmcblk0p2 rw rootwait 
```



