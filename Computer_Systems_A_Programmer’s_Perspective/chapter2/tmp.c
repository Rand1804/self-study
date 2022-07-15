#include <stdio.h>

// xp in %rdi  yp in %rsi,  zp in %rdx
void decode1(short z, short y, short x) {
    short val = z + y - x;
    if (z > 5) {
        if (y > 2) {
            val = x / z;
        else
            val = x / y;
        }
    } else if (z < 3)
        val = z / y;
    return val;
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














