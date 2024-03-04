## Boot-up sequence

**Summary**

What is the boot-up sequence for Cortex-M3?

**Answer**[ARM官方回答](https://developer.arm.com/documentation/ka001328/latest)

The Cortex-M3 can only boot from address 0x0 from reset, however the vector table can be relocated during program execution, by writing to the Vector Table Offset Register at address 0xE000ED08.

The boot-up sequence for M3 is different to traditional ARM cores, in that the first fetch from address 0x0 is the initial value of the SP, the second value is reset vector, i.e. the starting address of program code. The other thing to note is that the vector table entries for Cortex-M3 are address values and not branch instructions like traditional ARM cores. Also creating a table entry with bit [0] clear generates an INVSTATE fault on the first instruction of the handler corresponding to this vector.

## 概述

![image-20240301053723618](assets/image-20240301053723618.png)

![image-20240301055019016](assets/image-20240301055019016.png)

![image-20240301055909956](assets/image-20240301055909956.png)

![image-20240301060424212](assets/image-20240301060424212.png)

> 在M7内核中就不存在这个问题，它将0x0000_0000分配给ITCM_RAM空间使用了

![image-20240303230017064](assets/image-20240303230017064.png)

![image-20240303230134632](assets/image-20240303230134632.png)

![image-20240303231602017](assets/image-20240303231602017.png)

## NAND存储、U盘、SD卡升级

![image-20240303232229317](assets/image-20240303232229317.png)

![image-20240303232206974](assets/image-20240303232206974.png)

### APP

#### 1.修改中断向量表地址

![image-20240303233026671](assets/image-20240303233026671.png)

> 在system文件中修改中断向量表的偏移，与连接设置中的地址对应一下

#### 2.在app程序文件末尾增加CRC校验

![image-20240304012948415](assets/image-20240304012948415.png)

![image-20240304013904046](assets/image-20240304013904046.png)

## AES加密

![image-20240304024201301](assets/image-20240304024201301.png)

## CANFD、I2C、SPI和串口的固件更新实现

![image-20240304025641564](assets/image-20240304025641564.png)

![image-20240304030035063](assets/image-20240304030035063.png)

![image-20240304031143153](assets/image-20240304031143153.png)

![image-20240304031532699](assets/image-20240304031532699.png)