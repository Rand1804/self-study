#include "csapp.c"


int main(int argc, char **argv)
{
    struct in_addr inaddr;
    uint32_t addr;
    char buf[MAXBUF];

    if (argc != 2) {
        fprintf(stderr, "usage: %s <decimal number>\n", argv[0]);
        exit(0);
    }

    sscanf(argv[1], "%x", buf);
    inaddr.s_addr = 
}