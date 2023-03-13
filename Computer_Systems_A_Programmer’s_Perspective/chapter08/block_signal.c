#include "csapp.h"



int main()
{
    sigset_t mask, prev_mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    /* Block SIGINT and save previous blocked set */
    sigprocmask(SIG_BLOCK, &mask, &prev_mask);

    /* Code region that will not be */

    sigprocmask(SIG_SETMASK, &prev_mask, NULL);

}

