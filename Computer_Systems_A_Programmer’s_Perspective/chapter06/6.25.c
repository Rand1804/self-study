/*
 * The following table gives the parameters for a number of different caches.
 * For each cache, fill in the missing fields in the table.
 * Recall that m is the number of physical address bits, C is the cache size
 * (number of cache bytes), B is the block size in bytes, E is the associativity,
 * S is the number of cache sets, t is the number of tag bits, s is the 
 * number of set index bits, and b is the number of block offset bits.
 */

/*
Cache   m   C       B   E   S   t   s   b
1.      32  1024    4   4   64  24  6   2
2.      32  1024    4   256 1   30  0   2
3.      32  1024    8   1   128 22  7   3
4.      32  1024    8   128 1   29  0   3
5.      32  1024    32  1   32  22  5   5
6.      32  1024    32  4   8   24  3   5

Cache   m   C       B   E   S   t   s   b
1.      32  2048    8   1   256 21  8   3
2.      32  2048    4   4   128 23  7   2
3.      32  1024    2   8   64  25  6   1
4.      32  1024    32  2   16  23  4   5

CT-8
CI-2
CO-2

miss
hit     unkonwn
hit     C0

128
CT-8
CI-3
CO-2
hit
EB

miss

    dst array           src array
    0   1   2   3       0   1   2   3
0   m   m   m           m   m   h   m
1   
2
3

case1 miss rate 100%
case2 miss rate 25%
case3 miss rate 25%
D no because size is enough
E yes
