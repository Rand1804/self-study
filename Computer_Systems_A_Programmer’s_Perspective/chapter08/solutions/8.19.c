#include "csapp.h"
#include "csapp.c"

void foo(int n)
{
    int i;

    for (i = n-1; i > 0; i -= 2) {
        Fork();
    }
    printf("hello\n");
    exit(0);
}

int main()
{
    foo(8);
}