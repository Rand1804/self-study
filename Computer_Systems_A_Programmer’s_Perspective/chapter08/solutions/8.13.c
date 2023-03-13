#include "csapp.h"
#include "csapp.c"


int main()
{
    int a = 5;

    if (Fork() != 0)
        printf("a=%d\n", ++a);
    
    printf("a=%d\n", ++a);
    exit(0);
}