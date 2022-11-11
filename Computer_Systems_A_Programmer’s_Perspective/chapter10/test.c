#include "csapp.h"


int main()
{
    fork();
    printf("t");
    wait(NULL);
    printf("w");

}