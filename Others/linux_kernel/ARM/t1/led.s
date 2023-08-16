	.text
	@ 设置LED灯的配置寄存器GPX2CON[7]为输出状态
	ldr r0, =0x11000c40
	ldr r1, [r0]
	bic r1, #0xf0000000
	orr r1, #0x10000000
	str r1, [r0]
	@ 设置LED灯输出高电平   GPX2DAT
	ldr r0, =0x11000c44
	ldr r1, [r0]
	orr r1, #0x80
	str r1, [r0]
	.end