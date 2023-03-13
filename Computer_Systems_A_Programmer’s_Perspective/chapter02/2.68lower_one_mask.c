#include <stdio.h>

// assume 1<=n<=w

int lower_one_mask(int n) {
    int w = sizeof(int) << 3;
    unsigned mask = ((unsigned) -1) >> (w - n);
    return mask;
}

int main() {
    unsigned res = lower_one_mask(0);
    printf("%x", res);
}