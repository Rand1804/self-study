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

