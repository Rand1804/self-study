#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b) {
    unsigned pos_byte = ((unsigned) b) << (i << 3);
    unsigned mask = ((unsigned) 0xff) << (i << 3);
    unsigned res = (x & ~mask) | pos_byte;
    return res;
}

int main() {
    unsigned res = replace_byte(0x12345678, 0, 0xAB);
    printf("%x", res);
    return 0;
}