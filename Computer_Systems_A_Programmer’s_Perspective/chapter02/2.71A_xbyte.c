#include <stdio.h>

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum) {
    unsigned lshift_val = (3-bytenum) << 3;
    return (int) word << lshift_val >> 24;

}

int main() {
    int res = xbyte(0xAABBCCDD, 0);
    printf("%x", res);
    return 0;
}