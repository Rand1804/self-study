#include <stdio.h>

// x in %rdi  y in %rsi, val in %rbx
int decode1(int n) {
    int result = 1;
    do {
        result *= n;
        n = n - 1;
    } while (n > 1);
    return result;
}

int main() {
    int res = decode1(13);
    printf("%d", res);
}

/* 
* 0x100 0x100
* 0x108  0xffffff58
* 0x118  0x176
* 
*/

/*  
* int    <
* short          >=
*  unsigned char <=
*  long unsigned long pointer !=    
*/

/* 
* long   >=
* short  unsinged  short ==
* unsigned char      >
* int      <=
*/














