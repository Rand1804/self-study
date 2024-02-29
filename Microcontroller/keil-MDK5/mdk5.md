## Cortex-M简介

![image-20240228212834059](assets/image-20240228212834059.png)

![image-20240228212856578](assets/image-20240228212856578.png)

DSP扩展单元主要增加了一些DSP指令，算法比如FIR，FFR,IIR,FFT等。FPU是浮点数处理单元

![image-20240228213125385](assets/image-20240228213125385.png)

> 哈佛结构：数据和指令是分开的，有数据总线和指令总线，可以同时进行访问
>
> 冯诺依曼结构：数据和指令是在一起的，不能同时访问

![image-20240228213612459](assets/image-20240228213612459.png)

![image-20240228213806044](assets/image-20240228213806044.png)

> 芯片厂商从ARM公司购买了芯片的M3或M4内核之后，购买了这个内核还不行，芯片还需要加很多外设。像模数/数模转换模块，或者SRAM还有FLASH,都要添加相应的**IP核**。然后芯片厂商通过这些内部的CPU核加上外部组件的IP核，最终通过**流片**形成一个真正的芯片。*流片*（Tape Out），是指像流水線一樣通過一系列工藝步驟製造芯片，該詞在集成電路設計領域，“*流片*”指的是“試生產”。流片也很麻烦，费用几十万到几百万，可分为多少纳米的工艺。



## STM32简介

![image-20240228222735597](assets/image-20240228222735597.png)

![image-20240228222951218](assets/image-20240228222951218.png)

![image-20240228223257354](assets/image-20240228223257354.png)

![image-20240228224853051](assets/image-20240228224853051.png)

> In the context of software development, especially in embedded systems, DSP (Driver Support Package) and BSP (Board Support Package) are terms used to describe software components that facilitate the use of hardware.
>
> ### DSP (Driver Support Package)
>
> A Driver Support Package typically includes a set of drivers that operate at a lower level than the BSP. These drivers are responsible for managing the communication between the operating system and a specific hardware device. A DSP may include:
>
> - Peripheral drivers for components such as UARTs, SPI, I2C, etc.
> - Drivers for internal components like DMA controllers or timers.
> - Low-level code that directly interfaces with hardware registers.
>
> The DSP is usually closer to the hardware, dealing with the actual data transfers and signaling.
>
> ### BSP (Board Support Package)
>
> A Board Support Package is a layer of software that includes all of the system-level drivers, startup code, and other necessary libraries to boot an operating system and support a specific board or hardware platform. The BSP often includes:
>
> - Bootloader, which initializes the hardware and loads the operating system.
> - Device drivers from the DSP, along with any additional drivers for board-specific features.
> - Operating system adaptations or configurations specific to the board.
> - Memory management configurations, including setting up the memory map.
> - CPU or core initialization code and interrupt handling.
>
> The BSP makes sure that the operating system can run on the hardware by taking care of all the system-specific details. It acts as the foundation upon which the operating system and application code are built.
>
> ### Comparison
>
> While a BSP is comprehensive and includes everything needed to support a particular hardware platform or board, a DSP is usually a subset of a BSP, focusing solely on the drivers for specific hardware devices. The terms can sometimes be used interchangeably or vary in meaning depending on the context or the manufacturer's definitions, but generally, BSP is the broader term that encompasses the DSP within it.

![image-20240228225352763](assets/image-20240228225352763.png)

![image-20240228230043930](assets/image-20240228230043930.png)

## 板级软硬件

![image-20240228231308102](assets/image-20240228231308102.png)

![image-20240228231356861](assets/image-20240228231356861.png)

![image-20240228231518391](assets/image-20240228231518391.png)

![image-20240228231657235](assets/image-20240228231657235.png)

![image-20240228231840393](assets/image-20240228231840393.png)

> VBAT：电池供电，也就是电子供电，主要给RTC部分供电，电压为1.6-3.3V

![image-20240228232312111](assets/image-20240228232312111.png)

![image-20240228232420440](assets/image-20240228232420440.png)

![image-20240229013000479](assets/image-20240229013000479.png)

## 内存映射

![image-20240229013315632](assets/image-20240229013315632.png)

![image-20240229013518301](assets/image-20240229013518301.png)

![image-20240228212128042](assets/image-20240228212128042.png)

![image-20240229015717262](assets/image-20240229015717262.png)

![image-20240229014944266](assets/image-20240229014944266.png)

>  arm在授权之前是给了芯片的内存分配的粗线条，由芯片厂商具体定义细分

## 工程文件创建

![image-20240228022529083](assets/image-20240228022529083.png)

![image-20240228041812693](assets/image-20240228041812693.png)

勾选上微库，有利于printf函数中fputc的重定义，避免出问题

![image-20240228055926588](assets/image-20240228055926588.png)

勾选用于下载的hex文件

![image-20240228060241510](assets/image-20240228060241510.png)

![image-20240228060545609](assets/image-20240228060545609.png)

![image-20240228211222946](assets/image-20240228211222946.png)

![image-20240229023852556](assets/image-20240229023852556.png)

![image-20240229024737069](assets/image-20240229024737069.png)

## 标准固件库

![image-20240229045344982](assets/image-20240229045344982.png)

![image-20240229045622420](assets/image-20240229045622420.png)

![image-20240229045740721](assets/image-20240229045740721.png)

![image-20240229050410804](assets/image-20240229050410804.png)

> 一定要包含这个cortex-m3核心头文件路径

![image-20240229050748907](assets/image-20240229050748907.png)

> Device文件夹不是ARM提供的，而是ST自己提供的

![image-20240229054717824](assets/image-20240229054717824.png)

![image-20240229055343805](assets/image-20240229055343805.png)

> 因为ARM是授权给每个芯片厂商IP核，授权之后每个芯片厂商在他这个IP核的基础之上做自己的外设。而且他这个IP核也不是原封不动的直接用，IP核也是可以裁剪的，还可以在这个IP核的基础之上做一定的修改。如果说大家使用了不同的芯片厂商的Cortex-M内核，比如都用的M3内核，可以认为这些IP核他们内核一样的，基本上做一些内核的操作基本上都是兼容的。稍微有一些区别，大部分都是兼容的。这个就是CMSIS优势，深入到内核层之后，更换其他厂商也能兼容。

![image-20240228224853051](assets/image-20240228224853051.png)