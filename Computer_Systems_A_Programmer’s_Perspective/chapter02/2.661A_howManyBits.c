#include<stdio.h>

int howManyNits(int x) {
    // x >= 0 ? x : ~x
    int flag = x >> 31;
    x = (~flag & x) | (flag & ~x);
    int bit_16 = !!(x >> 16) << 4;
    x = x >> bit_16;
    int bit_8 = !!(x >> 8) << 3;
    x = x >> bit_8;
    int bit_4 = !!(x >> 4) << 2;
    x = x >> bit_4;
    int bit_2 = !!(x >> 2) << 1;
    x = x >> bit_2;
    int bit_1 = !!(x >> 1);
    x = x >> bit_1;
    int bit_0 = x;
    return bit_16 + bit_8 + bit_4 + bit_2 + bit_1 + bit_0 + 1;
}

int main() {
    int res;
    int num = 1;
    res = howManyNits(num);
    printf("%d\t %.8x", res, num);
    return 0;
}