#include <unistd.h>
#include <stdio.h>


unsigned int snooze(unsigned int secs) 
{
    int tmp = sleep(secs);
    tmp = secs - tmp;
    printf("Slept for %d of %d secs.", tmp, secs);

}

int main() 
{
    snooze(5);
}