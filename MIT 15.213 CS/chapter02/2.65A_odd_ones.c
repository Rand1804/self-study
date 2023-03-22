#include <stdio.h>

/* 
* Return 1 when x contains an odd number of 1s; 0 otherwise.
* Assume w=32
*/
int odd_ones(unsigned x) {
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x &= 1;
}

int odd_ones_lookup_table(unsigned x) {
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x &= 0xf;
    return (0x6996 >> x) & 1;
}

/*
* 0x6996 represents a bit vector of the numbers 1, 2, 4, 7, 8, 11, 13, and 14. 
* All of the 4-bit values that can be represented by an odd number of bits. 
* In 0x6996, a bit is set if its position in the vector corresponds
with (1, 2, 4, 7, 8, 11, 13, or 14).0x6996 is a tiny lookup table.
*/

int main() {
    unsigned num = 14;
    int res = odd_ones(num);
    printf("%d", res);
}