long data[MAXELEMS];    /* Global array to traverse */

/* test - Iterate over first "elems" elements of
 *        array "data" with stride of "stride", using
 *        using 4*4 loop unrolling.
 */

int test(int elems, int stride) {
    long i, s2=stride*2, s3=stride*3, s4=stride*4;
    long acc0 = 0, acc1 = 0, acc2 = 0, acc3 = 0;
    long length = elems, limit = length - s*4; 
}