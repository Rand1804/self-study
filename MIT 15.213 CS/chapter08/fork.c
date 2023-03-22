#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}



pid_t Fork(void)
{   
    int pid;
    if ((pid = fork()) < 0) 
        unix_error("Fork error");
    
    return pid;
}


int main()
{
    int x = 1;
    int pid;
    pid = Fork();
    if (pid == 0) {
        printf("child process pid: %d\n", ++x);
        exit(0);
    }

    printf("ppid: %d\n", --x);

    return 0;

}