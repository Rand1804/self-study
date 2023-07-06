#include "net.h"

int main(void) {
    int fd = -1;
    struct sockaddr_in sin;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(1);
    }

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
    if (bind(fd, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("bind error");
        exit(1);
    }

    if (listen(fd, BACKLOG) < 0) {
        perror("listen error");
        exit(1);
    }

    int newfd = -1;
    newfd = accept(fd, NULL, NULL);
    if (newfd < 0) {
        perror("accept error");
        exit(1);
    }

    int ret = 1;
    char buf[BUFSIZ];
    bzero(buf, BUFSIZ);
    while(1) {
        do {
            ret = read(newfd, buf, BUFSIZ-1);
        } while(ret <0 && EINTR == errno);
        if (ret < 0) {
            perror("read error");
            exit(1);
        }

        // client closed
        if (!ret) {
            break;
        }

        printf("Receive data: %s\n", buf);

        if (!strncasecmp(buf, QUIT_STR, sizeof(QUIT_STR))) {
            printf("Client is exiting!\n");
            break;
        }
    }
    close(newfd);
    close(fd);

    return 0;
}