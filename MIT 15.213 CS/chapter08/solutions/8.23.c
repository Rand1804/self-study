#include "csapp.h"
#include "csapp.c"

#define N 5

int ccount = N;


void child_handler(int sig)
{   
    int olderr = errno;
    pid_t pid;

    while ((pid = waitpid(-1, NULL, 0)) > 0) {
        ccount--;
        Sio_puts("Handler reaped child");
        Sio_putl((long) pid);
        Sio_puts(" \n");
    }

    if (errno != ECHILD)
        Sio_error("wait error");
    
    errno = olderr;
    
    Sleep(2);
    return;
}


int main()
{
    int i;
    pid_t pid;

    Signal(SIGCHLD, child_handler);
    for (i = N; i > 0; i--) {
        if ((pid = Fork()) == 0) {
            Sleep(2);
            exit(0);
        }
    }
    printf("wwt");
    while (ccount)
        ;
}