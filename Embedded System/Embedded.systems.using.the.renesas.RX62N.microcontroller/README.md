# EMBEDDED SYSTEMS USING THE RENESAS RX62N MICROCONTROLLER

## 02 Concepts of Microcontrollers

```c
struct st_port4 {
    union {
        unsigned char BYTE;
        struct {
            unsigned char B7:1;
            unsigned char B6:1;
            unsigned char B5:1;
            unsigned char B4:1;
            unsigned char B3:1;
            unsigned char B2:1;
            unsigned char B1:1;
            unsigned char B0:1;
        } BIT;
    } DDR;
}
```

Set Switch 1 (Port 4 bit 0) as Input
`PORT4.DDR.BIT.B1 = 0;`

Set LED1 (Port D bit 0) as Output
`PORTD.DDR.BIT.B0 = 1;`
`PORTD.DR.BIT.B0 = 0;`
Line 1 sets LED1 as an output and line 2 switches on the LED.

Sets LEDs 1, 2, and 3 (Port D bit 0, 1, and 2) as Outputs

1. PORTD.DDR.BYTE = 0x07;
2. PORTD.DR.BYTE = 0xF8;
Line 1 sets LED1, 2, and 3 as outputs and line 2 switches on the LEDs
