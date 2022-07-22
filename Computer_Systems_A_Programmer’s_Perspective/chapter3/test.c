void rfun(unsigned long x) {
    int *Aptr = &A[0][0];
    int result = 0;
    int count = 0;
    do {
        result += *Aptr + 68;
        count++;
    }while (count < N);
    return result;
}