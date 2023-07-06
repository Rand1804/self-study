#include "net.h"


int main() {
    int fd = -1;
    struct sockaddr_in sin;

    /* Create a socket descriptor */
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(1);
    }

    /* Connect to the server */
    bzero(&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(SERV_PORT);
#if 0
    sin.sin_addr = inet_addr(SERV_IP_ADDR);
#else
    if (inet_pton(AF_INET, SERV_IP_ADDR, (void *) &sin.sin_addr.s_addr) != 1) {
        perror("inet_pton error");
        exit(1);
    }
#endif

    if (connect(fd, (struct sockaddr *) &sin, sizeof(sin)) < 0)
        perror("connect error");
        exit(1);

}
