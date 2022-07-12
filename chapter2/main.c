#include<stdio.h>

int howManyNits(int x) {
    // +x
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x - (x >> 1);
}

int main() {
    int res;
    int num = 0;
    res = logicalNeg(num);
    printf("%d\t %d", res, !num);
    return 0;
}
