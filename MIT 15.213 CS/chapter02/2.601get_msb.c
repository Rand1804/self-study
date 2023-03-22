#include <stdio.h>

int get_msb(int x) {
    int shift_val = (sizeof(int)-1) << 3;
    int xright = x >> shift_val;
    return xright & 0xFF;

}

int main() {
    get_msb(0xab123456);
    return 0;
}