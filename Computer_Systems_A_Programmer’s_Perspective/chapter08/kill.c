#include "csapp.h"


int main()
{
    pid_t pid;
    printf("iiiiii\n");

    /* Child sleeps until SIGKILL signal received, then dies */
    if ((pid = Fork()) == 0) {
        printf("i am here\n");
        pause();        /* Wait for a signal to arrive */
        printf("control should never reach here!\n");
        exit(0);
    }

    /* Parent sends a SIGKILL signal to a child */
    kill(pid, SIGKILL);
    exit(0);
}