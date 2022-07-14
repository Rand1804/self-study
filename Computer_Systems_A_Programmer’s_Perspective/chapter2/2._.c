int isAsciiDigit(int x) {
    !((x >> 4) ^ 0x3) & (((x & 0xf) + (~0xa + 1)) >> 31);
}