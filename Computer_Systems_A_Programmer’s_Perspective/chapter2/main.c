#include<stdio.h>

int floatScale2(unsigned uf) {
    // s, exp, frac
    unsigned s = (uf >> 31) & 0x1;
    unsigned exp = (uf >> 23) & 0xff;
    unsigned frac = uf & 0x7fffff;
    // inifity or not an number
    if (exp == 0xff)
        return 0x80000000u;
    // denormalize
    if (exp == 0x00) {
        return 0;
    }
    // normalize
    frac |= 0x800000;
    int bias = exp - 127;
    if (bias < 0) {
        return 0;
    }
    else {
        frac >>= 23 - bias; 
        if (s == 1){
            frac = frac << (31 - bias) >> (31 - bias);
        }
    }
    return frac;
}

int main() {
    floatScale2(0x1100001101000100010001000);
    return 0;
}
