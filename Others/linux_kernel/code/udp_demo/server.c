#include "net.h"

int main() {
    int fd = -1;
    struct sockaddr_in sin;

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    int b_reuse = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &b_reuse, sizeof(int));

    bzero(&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(SERV_PORT);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(fd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("bind");
        exit(1);
    }

    char buf[BUFSIZ];
    struct sockaddr_in cin;
    socklen_t addrlen = sizeof(cin);
    char ipv4_addr[16];
    while(1) {
        bzero(buf, BUFSIZ);
        if (recvfrom(fd, buf, BUFSIZ-1, 0, (struct sockaddr *)&cin, &addrlen) < 0) {
            perror("recvfrom");
            continue;
        }

        
        if(!inet_ntop(AF_INET, (void *)&cin.sin_addr, ipv4_addr, sizeof(ipv4_addr))) {
            perror("inet_ntop");
            exit(1);
        } 

        printf("Recived form(%s:%d), data:%s", ipv4_addr, ntohs(cin.sin_port), buf);

        if (!strncasecmp(buf, QUIT_STR, strlen(QUIT_STR))) {
            printf("Client(%s:%d) is exiting!\n", ipv4_addr, ntohs(cin.sin_port));
        }
    }

    close(fd);
    return 0;

}