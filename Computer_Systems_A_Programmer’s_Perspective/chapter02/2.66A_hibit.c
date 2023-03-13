#include <stdio.h>

unsigned hibit(unsigned n) {
    n |= (n >>  1u);
    n |= (n >>  2u);
    n |= (n >>  4u);
    n |= (n >>  8u);
    n |= (n >> 16u);
    return n - (n >> 1);
}

int main() {
    int res = hibit(45);
    printf("%d", res);
}