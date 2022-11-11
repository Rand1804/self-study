#include "csapp.h"
#include "csapp.c"

int main()
{
    printf("p");fflush(stdout);

    if (fork() != 0) {
        printf("q");fflush(stdout);
        return 0;
    }else{
        printf("r");fflush(stdout);
        Waitpid(-1, NULL, 0);
    }
    return 0;
}