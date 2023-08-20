/*
    Display characters through serial port COM2.
*/

#define GPA1CON     (*(volatile unsigned int *)0x11400020)
#define ULCON2      (*(volatile unsigned int *)0x13820000)
#define UCON2       (*(volatile unsigned int *)0x13820004)
#define UBRDIV2     (*(volatile unsigned int *)0x13820028)
#define UFRACVAL2   (*(volatile unsigned int *)0x1382002c)
#define UTRSTAT2    (*(volatile unsigned int *)0x13820010)
#define UTXH2       (*(volatile unsigned int *)0x13820020)

// Interrupt
#define GPX1CON         (*(volatile unsigned int *)0x11000c20)
#define EXT_INT41_CON   (*(volatile unsigned int *)0x11000e04)
#define EXT_INT41_MASK  (*(volatile unsigned int *)0x11000f04)
#define ICDISER1_CPU0   (*(volatile unsigned int *)0x10490104)
#define ICDIPTR14_CPU0  (*(volatile unsigned int *)0x10490838)
#define ICDDCR          (*(volatile unsigned int *)0x10490000)
#define ICCICR_CPU0     (*(volatile unsigned int *)0x10480000)
#define ICCPMR_CPU0     (*(volatile unsigned int *)0x10480004)

#define ICCIAR_CPU0     (*(volatile unsigned int *)0x1048000c)
#define EXT_INT41_PEND  (*(volatile unsigned int *)0x11000f44)
#define ICDICPR1_CPU0   (*(volatile unsigned int *)0x10490284)
#define ICCEOIR_CPU0    (*(volatile unsigned int *)0x10480010)

// Pulse Width Modulation
#define GPD0CON         (*(volatile unsigned int *)0x114000a0)
#define TCFG0           (*(volatile unsigned int *)0x139d0000)
#define TCFG1           (*(volatile unsigned int *)0x139d0004)
#define TCON            (*(volatile unsigned int *)0x139d0008)
#define TCNTB0          (*(volatile unsigned int *)0x139d000c)
#define TCMPB0          (*(volatile unsigned int *)0x139d0010)


void uart_init() {
    // 1. Set pin GPA1_0 and GPA1_1 to UART mode.
    GPA1CON &= ~0xff;
    GPA1CON |= 0x22;
    // 2. Set UART parameters.
    ULCON2 = 0x3;
    UCON2 = 0x5;
    // DIV_VAL = (SCLK_UART/(bps * 16)) - 1
    // SCLK_UART = 100MHz
    // bps = 115200
    // DIV_VAL = 53.2534722222
    UBRDIV2 = 53;
    UFRACVAL2 = 4;

}

void uart_putc(char c) {
    // Wait until tx buffer is empty.
    while (!(UTRSTAT2 & 0x2));
    // Write character to tx buffer.
    UTXH2 = c;
}


void interrupt_init() {
    /* 1. General Purpose Input/Output(GPIO) Control */
    // set gpx1_1 interrupt mode
    GPX1CON &= ~(0xf << 4);
    GPX1CON |= 0xf << 4;
    // set interrupt controller
    EXT_INT41_CON &= ~(0x7 << 4);
    EXT_INT41_CON |= 0x2 << 4;
    // set interrupt mask
    EXT_INT41_MASK &= ~(0x1 << 1);

    /* 2. Generic Interrupt Controller */
    /* Distributor */
    // ICD: Interrupt Controller Distributor
    // Interrupt Set-Enable Register
    ICDISER1_CPU0 |= 0x1 << 25;
    // Interrupt Processor Targets Register
    ICDIPTR14_CPU0 |= 0x1 << 8;
    // Distributor Control Register
    ICDDCR |= 0x1;
    /* CPU Interface */
    // ICC: Interrupt Controller CPU Interface
    // Interface Control Register
    ICCICR_CPU0 |= 0x1;
    // Priority Mask Register
    ICCPMR_CPU0 |= 0xff;
    
}



void do_irq() {
    int irq_num;
    // Read IRQ number.
    // Interrupt Acknowledge Register
    irq_num = ICCIAR_CPU0 & 0x3ff;
    
    switch (irq_num) {
        case 57:
            uart_putc('I');
            // Interrupt Clear-Pending Register
            EXT_INT41_PEND |= 0x1 << 1;
            // Interrupt Clear-Pending Register
            ICDICPR1_CPU0 = 0x1 << 25;
            break;
        default:
            uart_putc('E');
            break;
    }
    // End of Interrupt Register
    ICCEOIR_CPU0 &= 0x3ff;
    ICCEOIR_CPU0 |= irq_num;
}


void pwm_init() {
    /* 1. General Purpose Input/Output(GPIO) Control */
    // set gpd0_0 to pwm mode
    GPD0CON = GPD0CON & ~(0xf << 0) | 0x2;
    /* 2. Pulse Width Modulation */
    // TOUT = PCLK / (prescaler value + 1) / (divider value + 1) / (counter value + 1)
    // TOUT = 100MHz / (99 + 1) / (8 + 1) / (199 + 1) = 555.56Hz
    // set PWM timer prescaler
    TCFG0 = TCFG0 & ~(0xff << 0) | 99;  // Timer Configuration
    // set PWM timer divider
    TCFG1 = TCFG1 & ~(0xf << 0) | 0x3;  
    // set PWM timer count buffer
    TCNTB0 = 199;   // Timer Count Buffer
    // set PWM timer compare buffer
    TCMPB0 = 99;   // Timer Compare Buffer
    // update PWM timer count buffer and compare buffer
    TCON = TCON & ~(0xf << 0) | 0xa;
    // TCON = TCON & ~(0xf << 0) | 0x2;
    // start PWM timer
    TCON = TCON & ~(0xf << 0) | 0x9;
}

int main() {
    uart_init();
    interrupt_init();
    pwm_init();
    while (1) {
        uart_putc('A');
        delay1s();
    }
}