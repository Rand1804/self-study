#include <stdio.h>

// assume 1 <= n <= w
int fits_bits(int x, int n) {
    int w = sizeof(int) << 3;
    int offset = w - n;
    return (x << offset >> offset) == x;
}

int main() {
    int res = fits_bits(34, 7);
    printf("%x", res);
}