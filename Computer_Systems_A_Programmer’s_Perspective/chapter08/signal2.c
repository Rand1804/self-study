#include "csapp.h"


void sigint_handle()
{
    return;
}

unsigned int snooze(unsigned int secs) 
{
    int tmp = sleep(secs);
    tmp = secs - tmp;
    
    printf("Slept for %d of %d secs.\n", tmp, secs);

}


int main() 
{   
    if (signal(SIGINT, SIG_IGN) == SIG_ERR)
        printf("signal error");
    snooze(5);
}