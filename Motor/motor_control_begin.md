![[Pasted image 20240926135515.png]]

速度控制器，蒸汽调速器或飞球调速器

![[Pasted image 20240926151134.png]]

![[Pasted image 20240926154838.png]]

![[Pasted image 20240926155858.png]]

![[Pasted image 20240926161349.png]]

![[Pasted image 20240926161736.png]]

### 直流有刷电机
![[Pasted image 20240927092449.png]]
![[Pasted image 20240927163825.png]]
![[Pasted image 20240927171813.png]]
#### 4.1 H桥驱动原理
![[Pasted image 20240928223125.png]]
![[Pasted image 20240928232611.png]]
#### 4.2 电流采集电路

![[Pasted image 20240929014617.png]]
#### 4.3 电压采集电路

![[Pasted image 20240929015232.png]]
#### 4.4 温度采集电路
![[Pasted image 20240929015510.png]]
### 直流有刷电机编程控制
![[Pasted image 20240929020439.png]]
因为mos管的打开和关断都是需要一定时间的,所以不能0时切换.半桥芯片本身自带一个**死区控制**,一般为**520ns**.如果这个时间还是不能满足器件,需要从软件上加延迟.
![[Pasted image 20240929021123.png]]
![[Pasted image 20240929021404.png]]
![[Pasted image 20240929021732.png]]
```c
/* 电机初始化 */
void dcmotor_init(void)
{
	GPIO_InitTypeDef gpio_init_struct;

	__HAL_RCC_GPIOF_CLK_ENABLE();

	gpio_init_struct.Pin = GPIO_PIN_10;
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_struct.Pull = GPIO_PULLDOWN;
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOF, &gpio_init_struct);

	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_RESET);
}

/* 电机开启 */
void dcmotor_start()
{
	/* 开启定时器 */
	HAL_TIM_Base_Start(&g_atimx_cplm_pwm_handle);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_SET);
}


/* 电机开启 */
void dcmotor_stop()
{
	/* 关闭定时器 */
	HAL_TIM_Base_Stop(&g_atimx_cplm_pwm_handle);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_RESET);
}


/* 电机反转 */
void dcmotor_dir(uint8_t para)
{
	HAL_TIM_PWM_Stop(&g_atimx_cplm_pwm_handle, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Stop(&g_atimx_cplm_pwm_handle, TIM_CHANNEL_1);

	if (para == 0) {
		HAL_TIM_PWM_Start(&g_atimx_cplm_pwm_handle, TIM_CHANNEL_1);
	}
	else if(para == 1) {
		HAL_TIMEx_PWMN_Start(&g_atimx_cplm_pwm_handle, TIM_CHANNEL_1);
	}
}


/* 设置电机转速 */
void dcmotor_speed(uint16_t para)
{
	/* 限速 */
	if (para < (__HAL_TIM_GetAutoreload(&g_atimx_cplm_pwm_handle) - 0x0F)) {
		__HAL_TIM_SetCompare(&g_atimx_cplm_pwm_handle, TIM_CHANNEL_1, pare);
	}
}






int main()
{
	/* 初始化定时器 */
	atim_timx_cplm_pwm_init(8400-1, 0);

	/* 初始化电机 */
	dcmotor_init();

	/* 开启电机 */
	dcmotor_start();
	/* 正转 */
	dcmotor_dir(0);
}



```

### 编码器
**编码器**:一种将直线位移,角位移转换为**脉冲信号**或**二进制编码**的设备.
![[Pasted image 20240929222533.png]]

![[Pasted image 20240929222547.png]]
![[Pasted image 20240929222603.png]]
![[Pasted image 20240929222626.png]]
![[Pasted image 20240929223157.png]]
![[Pasted image 20240929223600.png]]
![[Pasted image 20241007215825.png]]
![[Pasted image 20241007220049.png]]
![[Pasted image 20241007220451.png]]
#### 编码器测速
###### 编码器测速相关参数
- 编码器分辨率-- 11 PPR 每旋转一周能够输出11个脉冲
- 编码器供电-- DC 5V 直流5V
- 电机减速比-- 30:1  300RPM/30 得到最终输出转速
![[Pasted image 20241007222018.png]]
![[Pasted image 20241007222118.png]]
![[Pasted image 20241007230308.png]]
```c
#include "./BSP/TIMER/gtim.h"

#include "./BSP/LED/led.h"

  

/****************************************************************************************************/

  

TIM_HandleTypeDef g_timx_encode_chy_handle; /* 定时器x句柄 */

TIM_Encoder_InitTypeDef g_timx_encoder_chy_handle; /* 定时器编码器句柄 */

  

/************************************ 课堂代码功能1 编码器计数**************************************/

  

/**

* @brief 通用定时器 编码器接口初始化

* @param arr: 自动重装值。

* @param psc: 时钟预分频数

* @retval 无

*/

void gtim_timx_encoder_chy_init(uint16_t arr, uint16_t psc)

{

GPIO_InitTypeDef gpio_init_struct;

  

/************************************ 第一步 开启IO、定时器时钟 **********************************/

__HAL_RCC_GPIOC_CLK_ENABLE(); /* 开启GPIOC（通道1、2）的时钟 */

__HAL_RCC_TIM3_CLK_ENABLE(); /* 开启定时器3时钟 */

  

/************************************ 第二步 初始化编码器通道IO **********************************/

  

gpio_init_struct.Pin = GPIO_PIN_6 | GPIO_PIN_7; /* 通道1、2的IO口，即编码器的A、B相 */

gpio_init_struct.Mode = GPIO_MODE_AF_PP; /* 复用推挽输出 */

gpio_init_struct.Pull = GPIO_NOPULL; /* 不上下拉 */

gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH; /* 高速 */

gpio_init_struct.Alternate = GPIO_AF2_TIM3; /* IO复用，把IO作为定时器3功能 */

HAL_GPIO_Init(GPIOC, &gpio_init_struct);

  

/************************************ 第三步 配置定时器、编码器接口 *******************************/

  

g_timx_encode_chy_handle.Instance = TIM3; /* 定时器3 */

g_timx_encode_chy_handle.Init.Prescaler = psc; /* 定时器分频 */

g_timx_encode_chy_handle.Init.Period = arr; /* 自动重装载值 */

g_timx_encode_chy_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; /* 不分频 */

  

g_timx_encoder_chy_handle.EncoderMode = TIM_ENCODERMODE_TI12; /* TI1,TI2都检测 */

g_timx_encoder_chy_handle.IC1Polarity = TIM_ICPOLARITY_RISING; /* 边沿检测器设置，非反向 */

g_timx_encoder_chy_handle.IC1Selection = TIM_ICSELECTION_DIRECTTI; /* 通道1映射到IC1*/

g_timx_encoder_chy_handle.IC1Prescaler = TIM_ICPSC_DIV1; /* 不分频 */

g_timx_encoder_chy_handle.IC1Filter = 10; /* 滤波器设置 */

  

g_timx_encoder_chy_handle.IC2Polarity = TIM_ICPOLARITY_RISING; /* 边沿检测器设置，非反向 */

g_timx_encoder_chy_handle.IC2Selection = TIM_ICSELECTION_DIRECTTI; /* 通道2映射到IC2 */

g_timx_encoder_chy_handle.IC2Prescaler = TIM_ICPSC_DIV1; /* 一分频 */

g_timx_encoder_chy_handle.IC2Filter = 10; /* 滤波器设置 */

HAL_TIM_Encoder_Init(&g_timx_encode_chy_handle, &g_timx_encoder_chy_handle);

  

HAL_TIM_Encoder_Start(&g_timx_encode_chy_handle, TIM_CHANNEL_1); /* 开启编码器通道1 */

HAL_TIM_Encoder_Start(&g_timx_encode_chy_handle, TIM_CHANNEL_2); /* 开启编码器通道2 */

  

/************************************ 第四步 配置定时器中断 ***************************************/

  

HAL_NVIC_SetPriority(TIM3_IRQn, 2, 0); /* 抢占优先级2，响应优先级0 */

HAL_NVIC_EnableIRQ(TIM3_IRQn); /* 开启定时器3中断 */

__HAL_TIM_CLEAR_FLAG(&g_timx_encode_chy_handle, TIM_IT_UPDATE); /* 清除更新中断 */

__HAL_TIM_ENABLE_IT(&g_timx_encode_chy_handle, TIM_IT_UPDATE); /* 开启更新中断 */

}

  

/**

* @brief 定时器3中断服务函数

* @param 无

* @retval 无

*/

void TIM3_IRQHandler(void)

{

HAL_TIM_IRQHandler(&g_timx_encode_chy_handle);

}

  

volatile int g_timx_encode_count = 0; /* 用于记录溢出次数，向下溢出就-1，向上溢出就+1 */

  

/**

* @brief 定时器中断回调函数

* @param htim:定时器句柄指针

* @note 此函数会被定时器中断函数共同调用的

* @retval 无

*/

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)

{

if (__HAL_TIM_IS_TIM_COUNTING_DOWN(&g_timx_encode_chy_handle)) /* 判断CR1的DIR位 */

{

g_timx_encode_count--; /* DIR位为1，也就是递减计数 */

}

else

{

g_timx_encode_count++; /* DIR位为0，也就是递增计数 */

}

}

  

/**

* @brief 编码器计数

* @param 无

* @retval 当前总计数值

*/

int32_t gtim_get_encode(void)

{

/* 计算当前总计数值，当前总计数值 = 计数器当前值 + 溢出次数*65536 */

return (int32_t)(__HAL_TIM_GET_COUNTER(&g_timx_encode_chy_handle) + g_timx_encode_count * 65536);

}

  

/************************************ 课堂代码功能2 电机测速****************************************/

  

int32_t encode_old, encode_now, var;

  

/**

* @brief 电机速度计算

* @param 无

* @retval 电机速度

*/

int32_t speed_computer(void)

{

  

encode_now = gtim_get_encode(); /* 获取当前计数值 */

var = encode_now - encode_old; /* 计算计数变化量 */

encode_old = encode_now; /* 保存这一次的计数值 */

  

return (int32_t)(var * 5 * 60 / 4 / 11 / 30); /* 返回电机速度值 */

}

int main(void)

{

uint8_t i;

  

HAL_Init(); /* 初始化HAL库 */

sys_stm32_clock_init(336, 8, 2, 7); /* 设置时钟,168Mhz */

delay_init(168); /* 延时初始化 */

usart_init(115200); /* 串口初始化为115200 */

led_init(); /* 初始化LED */

gtim_timx_encoder_chy_init(0XFFFF, 0); /* 不分频直接84M的计数频率 */

  

while (1)

{

i++;

if (i % 20 == 0)

{

LED0_TOGGLE();

printf("编码器的计数值为：%d\r\n", gtim_get_encode()); /* 打印编码器计数值 */

  

printf("电机转速：%d RPM\r\n", speed_computer());

printf("\r\n");

}

delay_ms(10);

}

}



```
![[Pasted image 20241007230324.png]]

### 一阶低通滤波
低通: 指滤掉高频的部分
![[Pasted image 20241007232023.png]]
![[Pasted image 20241007232042.png]]
![[Pasted image 20241007232310.png]]

```c
/* 设置**定时器中断**每1ms计算一次电机速度 */

void speed_computer(int32_t encode_now, uint8_t ms)
{
	uint8_t i = 0, j = 0;
	float temp = 0.0;
	static uint8_t sp_count = 0, k = 0;
	/* 存储速度进行滤波计算 */
	static float speed_arr[10] = {0.0};

	/* 50ms 计算一次 */
	if (sp_count == ms) {
		/**
		 * 计算电机转速
		 * 第一步: 计算50ms计数变化量
		 * 第二步: 计算1min内计数变化量: g_encode.speed * (1000 / ms) * 60.0,
		 * 第三步: 除以编码器旋转一圈的计数次数(倍频倍数 * 编码器分辨率)
		 * 第四步: 除以减速比即可得出电机转速
		*/
		g_encode.encode_now = encode_now;
		g_encode.speed = (g_encode.encode_now - g_encode.encode_old);

		speed_arr[k++] = (float) (g_encode.speed * ((1000 / ms) * 60.0) / REDUCTION_RATIO / RO)
		g_encode.encode_old = g_encode.encode_now;

		/* 累计10次速度值, 后续进行滤波 */
		if (k == 10) {
			for (i = 10; i >= 1; i--) {
				for (j = 0; j < (i - 1); j++) {
					if (speed_arr[j] > speed_arr[j + 1]) {
						temp = speed_arr[j];
						speed_arr[j] = speed_arr[j + 1];
						speed_arr[j + 1] = temp;
					}
				}
			}
			temp = 0.0;

			/* 去除两边高低数据,将中间数值累加 */
			for (i = 2; i < 8; i++) {
				temp += speed_arr[i];
			}

			temp = (float) (temp / 6);

			g_motor_data.speed = (float) ((float) 0.48 * temp) + (g_motor_data.speed * (float) 0.52));
			k = 0;
		}
		sp_count = 0;
	}
	sp_count++;
}




```

![[Pasted image 20241008031336.png]]
### PID算法

![[Pasted image 20241008034535.png]]
![[Pasted image 20241008044528.png]]

![[Pasted image 20241008045322.png]]
```c

/* 增量式PID参数 */

#define KP 8.50f /* P参数*/

#define KI 5.00f /* I参数*/

#define KD 0.10f /* D参数*/




void pid_init(void)
{
	g_speed_pid.SetPoint = 0; /* 设定目标值 */
	g_speed_pid.ActualValue = 0.0; /* 输出期望值清零 */
	g_speed_pid.SumError = 0.0; /* 累计偏差 */
	g_speed_pid.Error = 0.0; /* Error[1] */
	g_speed_pid.LastError = 0.0; /* Error[-1] */
	g_speed_pid.PrevError = 0.0; /* Error[-2] */
	g_speed_pid.Proportion = KP; /* 比例常数 P */
	g_speed_pid.Integral = KI; /* 积分常数 I */
	g_speed_pid.Derivative = KD; /* 微分常数 D */
}



int32_t increment_pid_ctrl(PID_TypeDef *PID,float Feedback_value)
{
	PID->Error = (float)(PID->SetPoint - Feedback_value); /* 计算偏差 */

	PID->ActualValue += (PID->Proportion * (PID->Error - PID->LastError)) /* 比例项 */
						+ (PID->Integral * PID->Error) /* 积分项 */
						
						+ (PID->Derivative * (PID->Error - 2 * PID->LastError + PID->PrevError)); /* 微分项 */
	
	PID->PrevError = PID->LastError; /* 存储偏差，用于下次计算 */
	
	PID->LastError = PID->Error;

	return ((int32_t)(PID->ActualValue));
}
```



### 步进电机
![[Pasted image 20240927134038.png]]

![[Pasted image 20240927134509.png]]    
![[Pasted image 20240927135840.png]]
![[Pasted image 20240927140034.png]]
![[Pasted image 20240927143738.png]]
![[Pasted image 20240927144219.png]]
![[Pasted image 20240927144335.png]]
![[Pasted image 20240927145200.png]]
![[Pasted image 20240927145600.png]]
![[Pasted image 20240927145925.png]]
![[Pasted image 20240927173358.png]]
![[Pasted image 20240927173752.png]]

