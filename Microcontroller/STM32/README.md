# STM32

## 芯片信息

![image-20240106034554980](assets/image-20240106034554980.png)

![image-20240106040150483](assets/image-20240106040150483.png)

![image-20240106041050574](assets/image-20240106041050574.png)

![image-20240106042150280](assets/image-20240106042150280.png)

![image-20240106043738406](assets/image-20240106043738406.png)

![image-20240106043823674](assets/image-20240106043823674.png)

![image-20240106044421636](assets/image-20240106044421636.png)

![image-20240106052438217](assets/image-20240106052438217.png)

![image-20240106054503197](assets/image-20240106054503197.png)

## 引脚分布

![image-20240107225556774](assets/image-20240107225556774.png)

![image-20240107231236434](assets/image-20240107231236434.png)

### IO复用

![image-20240107231624433](assets/image-20240107231624433.png)

![image-20240107232019737](assets/image-20240107232019737.png)

![image-20240107232134018](assets/image-20240107232134018.png)

![image-20240107232323487](assets/image-20240107232323487.png)

### IO重映射

![image-20240107232544972](assets/image-20240107232544972.png)

![image-20240108013426591](assets/image-20240108013426591.png)

## GPIO

![image-20240108013800181](assets/image-20240108013800181.png)

### 寄存器组

![image-20240108014202494](assets/image-20240108014202494.png)

![image-20240108014434891](assets/image-20240108014434891.png)

![image-20240108015026727](assets/image-20240108015026727.png)

![image-20240108015136213](assets/image-20240108015136213.png)

![image-20240108015618931](assets/image-20240108015618931.png)

因为输入可以被多个片上外设和CPU同时读取，不会冲突

![image-20240108020018314](assets/image-20240108020018314.png)

**推挽**：P-MOS 和N-MOS 交替导通

**开漏**：P-MOS一直断开，即N-MOS的漏极一直断开，所以较开漏。写0输出低电平，写1 IO引脚就悬空了

![image-20240108021631186](assets/image-20240108021631186.png)

### 模拟模式

![image-20240108021938081](assets/image-20240108021938081.png)

![image-20240108022143885](assets/image-20240108022143885.png)

![image-20240108022336643](assets/image-20240108022336643.png)

![image-20240108022644878](assets/image-20240108022644878.png)

![image-20240108023217664](assets/image-20240108023217664.png)

![image-20240108023817232](assets/image-20240108023817232.png)

### 内部结构

![image-20240108024216341](assets/image-20240108024216341.png)

37个通用引脚中的一个

![image-20240108030437184](assets/image-20240108030437184.png)

真实信号会有一定抖动，但当负向递减时要低于VTL才会改变为0,所以对转换后的输出不影响。（滤波）

## LED实验

### 电路设计

![image-20240108031734243](assets/image-20240108031734243.png)

![image-20240108212632101](assets/image-20240108212632101.png)

### 代码结构

![image-20240108213244939](assets/image-20240108213244939.png)

![image-20240108213754874](assets/image-20240108213754874.png)

### GPIO初始化

![image-20240109043948987](assets/image-20240109043948987.png)

![image-20240109044042288](assets/image-20240109044042288.png)

每个外设都需要使能时钟，为了在不使用时最大程度的**省电**

![image-20240109045809575](assets/image-20240109045809575.png)

### GPIO读写

![image-20240109053647528](assets/image-20240109053647528.png)

![image-20240109054848552](assets/image-20240109054848552.png)

## 按钮实验

### 电路设计

![image-20240109055021594](assets/image-20240109055021594.png)

![image-20240109055441483](assets/image-20240109055441483.png)

![image-20240109060007901](assets/image-20240109060007901.png)

### 按键抖动

![image-20240109214405416](assets/image-20240109214405416.png)

![image-20240109214751592](assets/image-20240109214751592.png)

### 按键驱动库

![image-20240109220119026](assets/image-20240109220119026.png)

### 句柄

![image-20240109220519989](assets/image-20240109220519989.png)

### 回调函数

![image-20240109221546290](assets/image-20240109221546290.png)

### 多按键编程

![image-20240109223819707](assets/image-20240109223819707.png)

依次轮询

## AFIO

![image-20240109224421862](assets/image-20240109224421862.png)

### 复用功能重映射表

![image-20240109225200289](assets/image-20240109225200289.png)

![image-20240109225418440](assets/image-20240109225418440.png)

![image-20240109230554654](assets/image-20240109230554654.png)

**CH1N**: N表示negative,表示CH1的互补通道

**ETR**：外部参考信号

**BRKIN**：急停信号

### AFIO驱动

![image-20240109231927496](assets/image-20240109231927496.png)

![image-20240109232600117](assets/image-20240109232600117.png)

## 中断编程

![image-20240110014448074](assets/image-20240110014448074.png)

![image-20240110014622275](assets/image-20240110014622275.png)

![image-20240110015044131](assets/image-20240110015044131.png)

### 中断过程

![image-20240110015144150](assets/image-20240110015144150.png)

### 中断优先级

![image-20240110015525834](assets/image-20240110015525834.png)

![image-20240110023215622](assets/image-20240110023215622.png)

![image-20240110023413656](assets/image-20240110023413656.png)

### 中断的4种状态

![image-20240110024020443](assets/image-20240110024020443.png)

图4：A和B同时处于活动状态

## NVIC

![image-20240110024258276](assets/image-20240110024258276.png)

### 中断协作模型

![image-20240110024849918](assets/image-20240110024849918.png)

> GPIO、AFIO是不能产生中断源的
>
> NVIC负责保持现场和恢复现场，以及中断优先级设置和仲裁

### NVIC内部结构

![image-20240110025523172](assets/image-20240110025523172.png)

### 中断向量表

![image-20240110030156814](assets/image-20240110030156814.png)

![image-20240110030804280](assets/image-20240110030804280.png)

![image-20240110030954395](assets/image-20240110030954395.png)

### NVIC标准库接口

![image-20240110031337035](assets/image-20240110031337035.png)

![image-20240110031524200](assets/image-20240110031524200.png)

![image-20240110031854964](assets/image-20240110031854964.png)

### 具体程序

![image-20240110032533234](assets/image-20240110032533234.png)

```c
int main(void) {
    // 中断优先级分组2
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    // 开启中断源
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    // 配置NVIC的USART1中断
    NVIC_InitTypeDef NVICInitStruct;
    NVICInitStruct.NVIC_IRQChannel = USART1_IRQn; // 中断源的名称
    NVICInitStruct.NVIC_IRQChannelPreemptionPriority = 0; // 抢占优先级
    NVICInitStruct.NVIC_IRQChannelSubPriority = 0; // 子优先级
    NVICInitStruct.NVIC_IRQChannelCmd = ENABLE; // 使能中断
    NVIC_Init(&NVICInitStruct);
    
    while(1);
}

// 使用同名函数对startup_stm32f10x_md.s中的同名弱函数进行覆盖
void USART1_IRQHandler(void) {
    // TODO
}
```

![image-20240110052931712](assets/image-20240110052931712.png)

> NVIC位于cortex-M3内核内部，芯片上电后，内核的时钟就会开启，且无法关闭

![image-20240110054627559](assets/image-20240110054627559.png)

## EXTI

![image-20240110055554554](assets/image-20240110055554554.png)

### 电路结构

![image-20240110060158434](assets/image-20240110060158434.png)

> 电路图中梯形表示复用器，3路中选择一路

### 事件

![image-20240110060827773](assets/image-20240110060827773.png)

> 在现在的STM32编程中很少用到