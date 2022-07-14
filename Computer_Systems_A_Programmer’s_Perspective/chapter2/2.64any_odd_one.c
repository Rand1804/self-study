#include <stdio.h>

/*
* Return 1 when any odd bit of x equals 1; 0 otherwise.
* Assume w=32 
*/
int any_odd_one(unsigned x) {
    return !!(x & 0xaaaaaaaa);
}

int main() {
    int res = any_odd_one(0xa2);
    printf("%x", res);
}