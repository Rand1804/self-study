#include "csapp.h"
#include "csapp.c"


#define N 5

int ccount = 0;

void child_handler(int sig)
{
    int olderrno = errno;
    pid_t pid;

    if ((pid = wait(NULL)) < 0)
        Sio_error("wait error");
    ccount--;
    Sio_puts("Handler reaped child ");
    Sio_putl((long)pid);
    Sio_puts(" \n");
    sleep(1);
    errno = olderrno;
}

void fork14()
{
    pid_t pid[N];
    int i;
    ccount = N;
    Signal(SIGCHLD, child_handler);

    for (i = 0; i < N; i++) {
        if ((pid[i] = Fork()) == 0) {
            Sleep(1);
            exit(0);
        }
    }
    while (ccount > 0)
        ;
}



int main()
{
    fork14();
}