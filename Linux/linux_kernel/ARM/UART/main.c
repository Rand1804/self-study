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



int main() {
    uart_init();
    while (1) {
        uart_putc('A');
    }
}