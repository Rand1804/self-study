#include <stdio.h>

unsigned srl(unsigned x, int k) {
    /* Perform shift arithmetically */
    unsigned xsra = (int) x >> k;
    int w = sizeof(int) << 3;
    int mask = (int) -1 << (w - k);
    return xsra & ~mask;
}

int sra(int x, int k){
    int xsrl = (unsigned) x >> k;
    int w = sizeof(int) << 3;
    int mask = (int) -1 << (w - k);
    int m = 1 << (w -1);
    mask &= !(x & m) - 1;
    return xsrl | mask;
}

int main() {
    unsigned res = srl(0xff23456, 8);
    sra(0xff23456, 8);
    printf("%x", res);
    return 0;
}