#include "../csapp.h"

int main()
{
    int i;

    for (i = 3; i > 0; i--) {
        Fork();
    }
    printf("Example\n");
    exit(0);
}


