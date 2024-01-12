# STM32

## 芯片信息

![image-20240111221141882](assets/image-20240111221141882.png)

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

### 8种工作模式

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

根据开发板的实际电路图来决定是开漏还是推挽

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

### EXTI通道

![image-20240110213401416](assets/image-20240110213401416.png)

![image-20240110213453310](assets/image-20240110213453310.png)

> **引脚编号相同的引脚同时只能有一路作为EXTI的输入**

![image-20240110214045124](assets/image-20240110214045124.png)

### EXTI寄存器组

![image-20240110214633808](assets/image-20240110214633808.png)

### EXTI标准库

![image-20240111013549390](assets/image-20240111013549390.png)

![image-20240110215348513](assets/image-20240110215348513.png)

> 虽然是片上外设，但是与芯片唤醒有关，所以时钟默认开启，且不可关闭

### 中断实验

![image-20240110224340404](assets/image-20240110224340404.png)

![image-20240110230147745](assets/image-20240110230147745.png)

![image-20240110231027217](assets/image-20240110231027217.png)

![image-20240110231055056](assets/image-20240110231055056.png)

![image-20240110231441623](assets/image-20240110231441623.png)

![image-20240110232033177](assets/image-20240110232033177.png)

![image-20240110232646231](assets/image-20240110232646231.png)

![image-20240111012157076](assets/image-20240111012157076.png)

![image-20240111013147259](assets/image-20240111013147259.png)

```C
int main(void) {
    // 中断优先级分组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    PAL_Init();
    
    // 1.初始化IO引脚
    // 将PA0和PA1分别设置为输入上拉模式
    // 开启GPIOA的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    // PA0, PA1
    GPIO_InitTypeDef GPIOInitStruct;
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIOInitStruct);
    
    // 2.配置EXTI的引脚映射
    // 开启AFIO的时钟
    RCC_APB2PeriphClockCmd(RCC_ABP2periph_AFIO, ENABLE);
    // PA0 -> EXTI0
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
    // PA1 -> EXTI1
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
    
    // 3.初始化EXTI
    // 3.1.初始化EXTI0
    EXTI_InitTypeDef EXTIInitStruct;
    EXTIInitStruct.EXTI_Line = EXTI_Line0;
    EXTIInitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTIInitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTIInitStruct.EXTI_LineCmd = ENABLE
    EXTI_Init(&EXTIInitStruct);
    // 3.2.初始化EXTI1
    EXTIInitStruct.EXTI_Line = EXTI_Line1;
    EXTIInitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTIInitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTIInitStruct.EXTI_LineCmd = ENABLE
    EXTI_Init(&EXTIInitStruct);
    
    // 4.初始化NVIC
    NVIC_InitTypeDef NVICInitStruct;
    // 4.1.EXTI0
    // 先从参考手册的中断向量表中找到中断编号，然后在标准库中找到枚举类型IRQn_Type，查到对应编号
    NVICInitStruct.NVIC_IRQChannel = EXTI0_IRQn;
    NVICInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVICInitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVICInitStruct);
    // 4.2.EXTI1
    NVICInitStruct.NVIC_IRQChannel = EXTI1_IRQn;
    NVICInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVICInitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVICInitStruct);
    
    // 5.初始化PC13
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIOInitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIOInitStruct);
    
    while(1);
}

void EXTI0_IRQHandler(void) {
    // 清除中断
    EXTI_ClearITPendingBit(EXTI_Line0);
    // 点亮LED PC13 <- 0
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
}

void EXTI1_IRQHandler(void) {
    // 清除中断
    EXTI_ClearITPendingBit(EXTI_Line1);
    
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
}
```

### 增强版实验

![image-20240111014757760](assets/image-20240111014757760.png)

![image-20240111014659044](assets/image-20240111014659044.png)

> **PA5 PA6共用一个中断源**

![image-20240111015056115](assets/image-20240111015056115.png)

![image-20240111015347336](assets/image-20240111015347336.png)

![image-20240111015449263](assets/image-20240111015449263.png)

![image-20240111020057731](assets/image-20240111020057731.png)

```c
int main(void) {
    // 中断优先级分组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    PAL_Init();
    
    // 1.初始化IO引脚
    // 将PA0和PA1分别设置为输入上拉模式
    // 开启GPIOA的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    // PA5, PA6
    GPIO_InitTypeDef GPIOInitStruct;
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIOInitStruct);
    
    // 2.配置EXTI的引脚映射
    // 开启AFIO的时钟
    RCC_APB2PeriphClockCmd(RCC_ABP2periph_AFIO, ENABLE);
    // PA5 -> EXTI5
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);
    // PA6 -> EXTI6
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource6);
    
    // 3.初始化EXTI
    // 3.1.初始化EXTI5
    EXTI_InitTypeDef EXTIInitStruct;
    EXTIInitStruct.EXTI_Line = EXTI_Line5;
    EXTIInitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTIInitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTIInitStruct.EXTI_LineCmd = ENABLE
    EXTI_Init(&EXTIInitStruct);
    // 3.2.初始化EXTI6
    EXTIInitStruct.EXTI_Line = EXTI_Line6;
    EXTIInitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTIInitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTIInitStruct.EXTI_LineCmd = ENABLE
    EXTI_Init(&EXTIInitStruct);
    
    // 4.初始化NVIC
    NVIC_InitTypeDef NVICInitStruct;
    // EXTI5, EXTI6共用一个中断源
    // 先从参考手册的中断向量表中找到中断编号，然后在标准库中找到枚举类型IRQn_Type，查到对应编号
    NVICInitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVICInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVICInitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVICInitStruct);

    
    // 5.初始化PC13
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIOInitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIOInitStruct);
    
    while(1);
}

void EXTI9_5_IRQHandler(void) {
    // 不要写else,因为两个可能同时发生
    if (EXTI_GetITStatus(EXTI_Line5) == SET) { // EXTI5
        // 清除中断源
        EXTI_ClearITPendingBit(EXTI_Line5);
        // 点灯
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
    }
    if (EXTI_GetITStatus(EXTI_Line6) == SET) { // EXTI6
        // 清除中断源
        EXTI_ClearITPendingBit(EXTI_Line6);
        // 灭灯
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
    }
}

```

### PAL库

![image-20240111020942351](assets/image-20240111020942351.png)

![image-20240111022652039](assets/image-20240111022652039.png)

![image-20240111023825662](assets/image-20240111023825662.png)

```C
#include "stm32f10x_pal_exti.h"

// PA5 PA6
// EXTI5
static PalEXTI_HandleTypeDef hEXTI5;
// EXTI6
static PalEXTI_HandleTypeDef hEXTI6;

static void OnEXTI5Triggered(void) {
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
}
static void OnEXTI6Triggered(void) {
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
}


int main(void) {
    PAL_Init();
    RCC_APB2PeriphClockCmd(RCC_ABP2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIOInitStruct;
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIOInitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIOInitStruct);
    
    hEXTI5.Init.GPIO.GPIOx = GPIOA;
    hEXTI5.Init.GPIO.GPIO_Pin = GPIO_Pin_5;
    hEXTI5.Init.GPIO.GPIO_Mode = GPIO_Mode_IPU;
    hEXTI5.Init.Exti.EXTI_Mode = EXTI_Mode_Interrupt;
    hEXTI5.Init.Exti.EXTI_Trigger = EXTI_Trigger_Rising;
    hEXTI5.Init.Interrupt.PreemptionPriority = 0;
    hEXTI5.Init.Interrupt.SubPriority = 0;
    hEXTI5.Init.CallbackFn = OnEXTI5Triggered;
    PAL_EXTI_Init(&hEXTI5);
    PAL_EXTI_LineCmd(&hEXTI5, ENABLE);
    
    hEXTI6.Init.GPIO.GPIOx = GPIOA;
    hEXTI6.Init.GPIO.GPIO_Pin = GPIO_Pin_6;
    hEXTI6.Init.GPIO.GPIO_Mode = GPIO_Mode_IPU;
    hEXTI6.Init.Exti.EXTI_Mode = EXTI_Mode_Interrupt;
    hEXTI6.Init.Exti.EXTI_Trigger = EXTI_Trigger_Rising;
    hEXTI6.Init.Interrupt.PreemptionPriority = 0;
    hEXTI6.Init.Interrupt.SubPriority = 0;
    hEXTI6.Init.CallbackFn = OnEXTI6Triggered;
    PAL_EXTI_Init(&hEXTI6);
    PAL_EXTI_LineCmd(&hEXTI6, ENABLE);
    
}

void EXTI9_5_IRQHandler(void) {
    PAL_EXTI_IRQHandler(&hEXTI5);
    PAL_EXTI_IRQHandler(&hEXTI6);
}
```

![image-20240111025015595](assets/image-20240111025015595.png)

## 单片机的编程原则

![image-20240111025214961](assets/image-20240111025214961.png)

### 多任务编程

![image-20240111025314404](assets/image-20240111025314404.png)

超声波测距传感器

锂电池完全没电后将无法充电，所以要防止过放

### 使用实时操作系统

![image-20240111025807097](assets/image-20240111025807097.png)

使用裸机多任务模型

![image-20240111030135873](assets/image-20240111030135873.png)

![image-20240111030230966](assets/image-20240111030230966.png)

![image-20240111030403070](assets/image-20240111030403070.png)

### LED闪灯实验

![image-20240111031328179](assets/image-20240111031328179.png)

![image-20240111031603904](assets/image-20240111031603904.png)

![image-20240111031730218](assets/image-20240111031730218.png)

![image-20240111032946650](assets/image-20240111032946650.png)

![image-20240111033355231](assets/image-20240111033355231.png)

![image-20240111033753504](assets/image-20240111033753504.png)

![image-20240111034325832](assets/image-20240111034325832.png)

```C
static PalButton_HandleTypeDef hButton;
static uint32_t ledBlinkMode = 0; // 0-慢闪 1-普通 2-快闪
static uint32_t ledBlinkInterval[] = {1000, 200, 50};
static uint32_t stage = 0;
static uint64_t ledLastToggleTime = 0;

static void LED_Init(void);
static void Buttton_Init(void);
static void Button_Detect_Proc(void);
static void OnButtonReleased(void);
static void LED_Blink_Proc(void);

int main(void) {
    LED_Init();
    Button_Init();
    
    while(1) {
        LED_Blink_Proc();
        Button_Detect_Proc();
    }
}

static void LED_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIOInitStruct;
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIOInitStruct.GPIO_Speed = GPIO_Speeed_2MHz;
    GPIO_Init(GPIOC, &GPIOInitStruct);
}

static void Button_Init(void) {
    hButton.Init.GPIOx = GPIOA;
    hButton.Init.GPIO_Pin = GPIO_Pin_0;
    hButton.Init.Button_Mode = Button_Mode_IPU;
    hButton.Init.ButtonPressedCallback = 0;
    hButton.Init.ButtonReleasedCallback = OnButtonReleased;
    
    PAL_Button_Init(&hButton);
}

static void Button_Detect_Proc(void) {
    PAL_Button_Proc(&hButton);
}

static void OnButtonReleased(void) {
    ledBlinkMode = (ledBlinkMode + 1) % 3;
}

static void LED_Blink_Proc(void) {
    switch(stage) {
        case 0: // 灭
            if (PAL_GetTick() - ledLastToggleTime > ledBlinkInterval[ledBlinkMode]) {
                GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET); //点亮
                ledLastToggleTime = PAL_GetTick();
                stage = 1;
            }
            break;
         case 1: // 亮
            if (PAL_GetTick() - ledLastToggleTime > ledBlinkInterval[ledBlinkMode]) {
                GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET); // 熄灭
                ledLastToggleTime = PAL_GetTick();
                stage = 0;
            }
            break;
    }
}
```

## 串口通信

![image-20240111035158158](assets/image-20240111035158158.png)

![image-20240111035651657](assets/image-20240111035651657.png)

**备注**：**电压基准**是指GND视为0V,3.3V则是比GND高3.3V

### 串口数据帧格式

![image-20240111040124830](assets/image-20240111040124830.png)

![image-20240111040145134](assets/image-20240111040145134.png)

![image-20240111040158569](assets/image-20240111040158569.png)

使用高电平表示**空闲**

![image-20240111040403669](assets/image-20240111040403669.png)

![image-20240111040442358](assets/image-20240111040442358.png)

![image-20240111040703245](assets/image-20240111040703245.png)

![image-20240111040800159](assets/image-20240111040800159.png)

在实际使用中例子1和例子4较多，因为8位为一个字节

![image-20240111041052025](assets/image-20240111041052025.png)

![image-20240111041110533](assets/image-20240111041110533.png)

![image-20240111041258188](assets/image-20240111041258188.png)

（连续发送要求中间没有空闲）？

### 同步和异步通信

![image-20240111041545736](assets/image-20240111041545736.png)

![image-20240111041622148](assets/image-20240111041622148.png)

### 波特率

![image-20240111041724215](assets/image-20240111041724215.png)

在空闲时一直采集监控状态，当发现开始后，间隔1.5个码元采集一个数据，之后间隔1个**码元**

**码元**：一个高电平或一个低电平称为一个码元

### 硬件流控

![image-20240111042108740](assets/image-20240111042108740.png)

发送方过快，导致接收方来不及处理，可以反馈一个信号给发送方，来控制发送速度

### 串口流控

![image-20240111042418863](assets/image-20240111042418863.png)

## USART

![image-20240111042752275](assets/image-20240111042752275.png)

F103C8T6只有前3个串口

![image-20240111043020811](assets/image-20240111043020811.png)

### 寄存器组

![image-20240111043742074](assets/image-20240111043742074.png)

### 串并转换电路

![image-20240111043906210](assets/image-20240111043906210.png)

![image-20240111044127562](assets/image-20240111044127562.png)

### 串并转换电路实现

![image-20240111044333801](assets/image-20240111044333801.png)

![image-20240111044528443](assets/image-20240111044528443.png)

### USART的基本模型

![image-20240111044949746](assets/image-20240111044949746.png)

### USART完整框图

![image-20240111045143964](assets/image-20240111045143964.png)

## USART参数配置

### 数据帧格式设置

![image-20240111050204598](assets/image-20240111050204598.png)

### 数据传输方向选择

![image-20240111050601963](assets/image-20240111050601963.png)

### 波特率设置

![image-20240111050930302](assets/image-20240111050930302.png)

![image-20240111051319570](assets/image-20240111051319570.png)

![image-20240111051357480](assets/image-20240111051357480.png)

### USART的总开关

![image-20240111051814989](assets/image-20240111051814989.png)

## USART数据发送过程

![image-20240111052121209](assets/image-20240111052121209.png)

![image-20240111052240420](assets/image-20240111052240420.png)

TDR寄存器和移位寄存器的双缓冲是连续发送的保障

![image-20240111052514675](assets/image-20240111052514675.png)

通过读取标志位来解决这两个问题

### SR状态寄存器

![image-20240111053131667](assets/image-20240111053131667.png)

![image-20240111053507638](assets/image-20240111053507638.png)

![image-20240111053842865](assets/image-20240111053842865.png)

![image-20240111053954428](assets/image-20240111053954428.png)

## USART数据接收过程

![image-20240111054152489](assets/image-20240111054152489.png)

![image-20240111054323880](assets/image-20240111054323880.png)

![image-20240111054535256](assets/image-20240111054535256.png)

![image-20240111054649997](assets/image-20240111054649997.png)

## USART错误标志位

![image-20240111054804684](assets/image-20240111054804684.png)

![image-20240111054839166](assets/image-20240111054839166.png)

![image-20240111054932207](assets/image-20240111054932207.png)

![image-20240111055216567](assets/image-20240111055216567.png)

**注意**：

**过采集**： 接收方采集时并不是简单的采集，而是采用过采样的方法。在采集时使用比较高的频率采集多次

对于串口来说，就是采用16倍的波特率采集码元正中间的数据，采集3次。如果3次不一致，则发生噪声错误

![image-20240111055503084](assets/image-20240111055503084.png)

接收的数据没有被即时读出来，导致移位寄存器数据在等待，如果此时收到第三个数据，则第二个数据会覆盖第一个数据，则发送**过载错误**

错误标志位仅对接收方有效

![image-20240111055715115](assets/image-20240111055715115.png)

一定要先备份SR寄存器，再读取数据，因为SR寄存器表示当前在RDR寄存器中数据的错误，如果该数据被读出，则SR寄存器会被清空。读完后再进行错误处理，避免过载错误

## USART标准库编程

![image-20240111221235213](assets/image-20240111221235213.png)

![image-20240111221550674](assets/image-20240111221550674.png)

![image-20240111222555567](assets/image-20240111222555567.png)

### UART_Init

![image-20240111222658147](assets/image-20240111222658147.png)

### USART_Cmd

![image-20240111223706627](assets/image-20240111223706627.png)

### USART_SendData

![image-20240111223810648](assets/image-20240111223810648.png)

### USART_ReceiveData

![image-20240111224025724](assets/image-20240111224025724.png)

### USART_GetFlagStatus

![image-20240111224049571](assets/image-20240111224049571.png)

### 代码编程

![image-20240111224513986](assets/image-20240111224513986.png)

#### IO引脚配置

![image-20240111224802322](assets/image-20240111224802322.png)

![image-20240111230538693](assets/image-20240111230538693.png)

> **TX**：推挽可以输出高低电平，开漏模式只能输出低电平和高阻抗，但在外接电路的情况下也可以输出高电平。**串口输出速率**最高不会超过2M，但是为了保险起见，选择10MHz
>
> **RX**：为了防止Rx线路断开，导致输入引脚悬空，引入空间中的电磁波的脏数据，所以要使用输入上拉或者下拉。然后因为UART协议高电平是空闲状态，所以断开后保持高电平比较合适，如果是低电平可能导致误输入0x00，接着没有停止位，触发FE帧格式错误。所以选择**上拉**模式
>
> **CTS**：输入上拉模式。因为该线路低电平有效
>
> **RTS**：复用推挽模式。输出高低电平。RTS动作的比Tx引脚要慢，输出速率随便。
>
> **CK**：向外输出时钟

![image-20240111230906530](assets/image-20240111230906530.png)

**双工**：表示数据的发送和接收是双向的，一方既可以接收数据，也可以发送数据

**半双工和全双工**：半双工表示在接收数据的同时就不能发送数据，在发送数据的同时就不能接收数据。两个方向的数据传输不能同时进行。全双工就表示两个方向的数据传输可以同时进行。半双工时，连接两边的TX引脚

![image-20240111231532180](assets/image-20240111231532180.png)

![image-20240112011235681](assets/image-20240112011235681.png)

![image-20240112011505131](assets/image-20240112011505131.png)

![image-20240112011635501](assets/image-20240112011635501.png)

![image-20240112012130811](assets/image-20240112012130811.png)

![image-20240112012411704](assets/image-20240112012411704.png)

![image-20240112012557941](assets/image-20240112012557941.png)

![image-20240112013651790](assets/image-20240112013651790.png)

#### 代码

```c
int main(void) {
    GPIO_InitTypeDef GPIOInitStruct;
    
    PAL_Init();
    
    // 初始化Tx PB6 AF_PP 10MHz
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIOInitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB, &GPIOInitStruct);
    
    // 初始化Rx PB7 IPU
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIOInitStruct);
    
    // 重映射USART1的Tx和Rx引脚
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
    
    // 使能USART1的时钟并初始化
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    USART_InitTypeDef USARTInitStruct;
    USARTInitStruct.USART_BaudRate = 9600;
    USARTInitStruct.USART_WordLength = USART_WordLength_8b;
    USARTInitStruct.USART_StopBits = USART_StopBits_1;
    USARTInitStruct.USART_Parity = USART_Parity_No;
    USARTInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USARTInitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USARTInitStruct);
    
    // 闭合USART1总开关
	USART_Cmd(USART1, ENABLE);
    
    // 初始化LED
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIOInitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIOInitStruct);
    
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
    
    // 发送数据
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, 0x5a);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    
    // 读取数据
    uint8_t c;
    
    while (1) {
        while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
        c = USART_ReceiveData(USART1);
        if (c == '0') {
            GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
        } else if (c == '1') {
            GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
        }
    }
}
```

### 中断方式的数据接收

![image-20240112014427807](assets/image-20240112014427807.png)

![image-20240112014602487](assets/image-20240112014602487.png)

![image-20240112014841169](assets/image-20240112014841169.png)

#### 中断共用

![image-20240112020006278](assets/image-20240112020006278.png)

![image-20240112020258737](assets/image-20240112020258737.png)

#### 编程接口

![image-20240112020617575](assets/image-20240112020617575.png)

###### USART_ITConfig

![image-20240112020947989](assets/image-20240112020947989.png)

###### USART_GetITStatus

![image-20240112021232415](assets/image-20240112021232415.png)

###### USART_ClearITPendingBit

![image-20240112021449402](assets/image-20240112021449402.png)

###### 处理时间

![image-20240112021627292](assets/image-20240112021627292.png)

###### 就地处理

![image-20240112021942196](assets/image-20240112021942196.png)

8字节0.8ms

###### 缓存后处理

![image-20240112022255243](assets/image-20240112022255243.png)

![image-20240112022449343](assets/image-20240112022449343.png)

#### 中断程序

![image-20240112023217465](assets/image-20240112023217465.png)

#### 清除中断

![image-20240112024228903](assets/image-20240112024228903.png)

**硬件置位，软件复位**：软件不直接写标志位，而是反向满足硬件置位条件来清除

```c
int main(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    PAL_Init();
    
    LED_Init();
    USART_Recv_Init();
    
}

static void LED_Init(void) {
    GPIO_InitTypeDef GPIOInitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIOInitStruct.Mode = GPIO_Mode_Out_OD;
    GPIOInitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIOInitStruct);
    
}

static void USART_Recv_Init(void) {
    GPIO_InitTypeDef GPIOInitStruct;
    // 初始化Tx PB6 AF_PP 10MHz
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIOInitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB, &GPIOInitStruct);
    
    // 初始化Rx PB7 IPU
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIOInitStruct);
    
    // 重映射USART1的Tx和Rx引脚
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
    
    // 使能USART1的时钟并初始化
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    USART_InitTypeDef USARTInitStruct;
    USARTInitStruct.USART_BaudRate = 9600;
    USARTInitStruct.USART_WordLength = USART_WordLength_8b;
    USARTInitStruct.USART_StopBits = USART_StopBits_1;
    USARTInitStruct.USART_Parity = USART_Parity_No;
    USARTInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USARTInitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USARTInitStruct);
    
    // 配置中断源
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    
    NVIC_InitTypeDef NVICInitStruct;
    NVICInitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVICInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVICInitStruct.NVIC_IRQChannelSubPriority = 0;
    NVICInitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVICInitStruct);
    
    // 闭合USART1总开关
	USART_Cmd(USART1, ENABLE);
}

void USART1_IRQHandler(void) {
    uint8_t c;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
        // 读取了数据，且由于RDR被读取，中断也被清除
        c = USART_ReceiveData(USART1);
        if (c == '0') {
            // 熄灯
            GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
        } else {
            GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
        }
    }
}
```

#### Echo实验（缓存处理）

![image-20240112032746422](assets/image-20240112032746422.png)

发送数据用时一定超过接收单个数据周期

#### 队列

![image-20240112033247190](assets/image-20240112033247190.png)

![image-20240112033438248](assets/image-20240112033438248.png)

![image-20240112033526975](assets/image-20240112033526975.png)

```c
#include "queue.h"

static Queue_HandleTypeDef hQueue;

int main(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    PAL_Init();
    USART_Echo_Init();
    
    while (1) {
        USART_Echo_Proc();
    }
}

static void USART_Echo_Init(void) {
    
    Queue_Init(&hQueue);
    
    // Init PB6 PB7
    GPIO_InitTypeDef GPIOInitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIOInitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB, &GPIOInitStruct);
    
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIOInitStruct);
    
    // AFIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
    
    // USART1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    USART_InitTypeDef USARTInitStruct;
    USARTInitStruct.USART_BaudRate = 9600;
    USARTInitStruct.USART_WordLength = USART_WordLength_8b;
    USARTInitStruct.USART_Parity = USART_Parity_No;
    USARTInitStruct.USART_StopBits = USART_Mode_Tx | USART_Mode_Rx;
    USARTInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1, &USARTInitStruct);
    
    // 配置中断
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    
    NVIC_InitTypeDef NVICInitStruct;
    NVICInitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVICInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVICInitStruct.NVIC_IRQChannelSubPriority = 0;
    NVICInitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVICInitStruct);
    
    // 闭合USART1总开关
    USART_Cmd(USART1, ENABLE);
    
}

void USART1_IRQHandler(void) {
    uint8_t c;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
        c = USART_ReceiveData(USART1);
        Queue_Enqueue(&hQueue, c);
    }
}

static uint8_t a[100];
static uint16_t cursor = 0;

static void USART_Echo_Proc(void) {
    uint8_t c;
    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
    ErrorStatus error = Queue_Dequeue(&hQueue, &c);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    if (error == SUCESS) {
        a[cursor++] = c;
        // 收到新行
        if (cursor > 2 && a[cursor-2] == 'r' && a[cursor-1] == '\n') {
            a[cursor] = '\0';
            USART1_SendString((const char *)a);
            cursor = 0;
        }
    }
}

static void USART1_SendString(const char *Str) {
    for (uint32_t i = 0; i < strlen(Str); i++) {
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    	USART_SendData(USART1, Str[i]);
    }
   	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}
```

#### 改进

为避免在进行出队操作时，中断到来进行入队操作，导致错误，在出队时屏蔽中断

### 中断方式的数据发送

![image-20240112042731347](assets/image-20240112042731347.png)

```c
#include "queue.h"

static Queue_HandleTypeDef RxHQueue;
static Queue_HandleTypeDef TxHQueue;

int main(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    PAL_Init();
    USART_Echo_Init();
    
    while (1) {
        USART_Echo_Proc();
    }
}

static void USART_Echo_Init(void) {
    
    Queue_Init(&RxHQueue);
    Queue_Init(&TxHQueue);
    
    // Init PB6 PB7
    GPIO_InitTypeDef GPIOInitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIOInitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB, &GPIOInitStruct);
    
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIOInitStruct);
    
    // AFIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
    
    // USART1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    USART_InitTypeDef USARTInitStruct;
    USARTInitStruct.USART_BaudRate = 9600;
    USARTInitStruct.USART_WordLength = USART_WordLength_8b;
    USARTInitStruct.USART_Parity = USART_Parity_No;
    USARTInitStruct.USART_StopBits = USART_Mode_Tx | USART_Mode_Rx;
    USARTInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1, &USARTInitStruct);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
    
    
    // 配置NVIC
    NVIC_InitTypeDef NVICInitStruct;
    NVICInitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVICInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVICInitStruct.NVIC_IRQChannelSubPriority = 0;
    NVICInitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVICInitStruct);
    
    // 闭合USART1总开关
    USART_Cmd(USART1, ENABLE);
    
}

void USART1_IRQHandler(void) {
    uint8_t c;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
        c = USART_ReceiveData(USART1);
        Queue_Enqueue(&RxHQueue, c);
    }
    if (USART_GetITStatus(USART1, USART_IT_TXE) == SET) {
        if (Queue_Dequeue(&hQueue, &c) == SUCCESS) {
            USART_SendData(USART1, c);
        } else {
            USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
        }
        
    }
}

static uint8_t a[100];
static uint16_t cursor = 0;

static void USART_Echo_Proc(void) {
    uint8_t c;
    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
    ErrorStatus error = Queue_Dequeue(&RxHQueue, &c);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    if (error == SUCESS) {
        a[cursor++] = c;
        // 收到新行
        if (cursor > 2 && a[cursor-2] == 'r' && a[cursor-1] == '\n') {
            a[cursor] = '\0';
            USART1_SendString((const char *)a);
            cursor = 0;
        }
    }
}

static void USART1_SendString(const char *Str) {
    USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
    for (uint32_t i = 0; i < strlen(Str); i++) {
        Queue_Enqueue(&TxHQueue, Str[i]);
    }
   	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
}
```

## USART PAL 库编程

![image-20240112045530562](assets/image-20240112045530562.png)

![image-20240112051209475](assets/image-20240112051209475.png)

![image-20240112051458751](assets/image-20240112051458751.png)

![image-20240112051746221](assets/image-20240112051746221.png)

![image-20240112051827970](assets/image-20240112051827970.png)

![image-20240112052144571](assets/image-20240112052144571.png)

![image-20240112052246171](assets/image-20240112052246171.png)

![image-20240112052408216](assets/image-20240112052408216.png) 

**超时等待**

![image-20240112052556983](assets/image-20240112052556983.png)

### 串口的波形监控

![image-20240112055509937](assets/image-20240112055509937.png)

![image-20240112060742289](assets/image-20240112060742289.png)
