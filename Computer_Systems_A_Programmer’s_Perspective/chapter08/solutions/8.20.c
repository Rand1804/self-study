#include "csapp.h"
#include "csapp.c"


int main(int argc, char *argv[], char *envp[])
{   

    Execve("/bin/ls", argv, envp);
}