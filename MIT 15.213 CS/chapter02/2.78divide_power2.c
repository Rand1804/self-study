#include <stdio.h>
#include <limits.h>

// assume 0 <= k < w-1
int divide_power2(int x, int k) {
    int neg_int = x & INT_MIN;
    int bias = (1 << k) - 1;
    neg_int && (x = x + bias);
    return x >> k; 
}

int main() {
    printf("%d\n", -7/8);
    int res = divide_power2(-7, 3);
    printf("res=%d", res);
}