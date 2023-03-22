int A(int x) {
    return !~x;
}

int B(int x) {
    return !x;
}

int C(int x) {
    unsigned mask = 0xff;
    return !~(x | ~mask);
}

int D(int x) {
    int shift_val = (sizeof(int) - 1) << 3;
    int x = x >> shift_val;
    int msb = x & 0xff;
    return !msb;
}