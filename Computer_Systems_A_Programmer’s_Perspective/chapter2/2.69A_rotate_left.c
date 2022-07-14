#include <stdio.h>
// assume 0<=n<w

/*
int rotate_left(unsigned x, int n) {
    int w = sizeof(int) << 3;
    unsigned mask = -1 << (w-n-1) << 1;
    unsigned hibit = (mask & x) >> (w-n-1) >> 1;
    return (x << n) | hibit;
}
*/

int rotate_left(unsigned x, int n) {
    int w = sizeof(int) << 3;
    return x << n | x >> (w-n-1) >> 1;
}

int main() {
    int res = rotate_left(0x12345678, 20);
    printf("%x", res);
}