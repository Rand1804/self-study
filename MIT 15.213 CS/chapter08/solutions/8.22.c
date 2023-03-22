#include "csapp.h"
#include "csapp.c"

int mysystem(char *command)
{
    pid_t pid;
    int status;

    if ((pid = Fork()) == 0) {
        char *argv[4] = {"/bin/sh", "-c", command, NULL};
        Execve("/bin/sh", argv, environ);
    }
    printf("child pid: %d\n", pid);

    if (Waitpid(pid, &status, 0) > 0) {
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        
        if (WIFSIGNALED(status))
            return WTERMSIG(status);
    }
}


int main()
{
    char command[MAXLINE];

    
    while (1) {
        printf("> ");
        fgets(command, MAXLINE, stdin);
        mysystem(command);
    }
    
}