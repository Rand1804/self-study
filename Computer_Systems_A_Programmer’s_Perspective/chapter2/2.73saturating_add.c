#include <stdio.h>
#include <limits.h>

int saturating_add(int x, int y) {
    int sum = x + y;
    int sign_mask = INT_MIN;
    // x>0, y>0, sum<0
    int pos_over = !(x & INT_MIN) && !(y & INT_MIN) && (sum & INT_MIN);
    // x<0, y<0, sum>=0
    int neg_over = (x & INT_MIN) && (y & INT_MIN) && !(sum & INT_MIN);
    
    pos_over && (sum = INT_MAX) || neg_over && (sum = INT_MIN);
    return sum;
}

int main() {
    int res = saturating_add(0xf0000000, 0xf0000021);
    printf("%x", res);
}