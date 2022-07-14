#include <stdio.h>
#include <limits.h>

int A(int k) {
    // 1^(w-k)0^k
    return -1 << k;
}

int B(int k, int j) {
    // 0^(w-k-j)1^k0^j
    return ~(-1 << k) << j;
}

int main() {
    int res = B(4,5);
    printf("%.8x", res);
}