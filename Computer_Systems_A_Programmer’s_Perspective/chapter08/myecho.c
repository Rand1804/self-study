#include <stdio.h>


int main(int argc, char *argv[], char *envp[]) 
{
    
    for (int i=0; envp[i] != 0; i++) {
        printf("envp[%2d]: %s\n", i, envp[i]);
    }
}
