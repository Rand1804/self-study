#include "csapp.h"
#include "csapp.c"

int child_handler(int sig)
{

    psignal(sig, stdout);
}


void end(void)
{
    printf("2");fflush(stdout);
}


int main()
{
    Signal(SIGCHLD, child_handler);
    char c[3];
    if (Fork() == 0)
        atexit(end);
    if (Fork() == 0) {
        printf("0");fflush(stdout);
        c[4] = 1;
    }else{
        printf("1");fflush(stdout);
    }
    while (1);
    exit(0);
}