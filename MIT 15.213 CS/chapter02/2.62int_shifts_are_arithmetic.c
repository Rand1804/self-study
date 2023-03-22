#include <stdio.h>

/*
int int_shifts_are_arithmetic() {
    int test_num = -1;
    int shift_val = (sizeof(int)-1) << 3;
    return !~(test_num >> shift_val);
}
*/

int int_shifts_are_arithemetic() {
    int num = -1;
    return !(num ^ (num >> 1));
}