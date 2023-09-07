#include "net.h"

void usage(char *s) {
    printf("This is udp demo!\n");
    printf("\nUsage:\n\t %s serv_ip serv_port", s);
    printf("\n\t serv_ip: udp server ip address");
    printf("\n\t serv_port: udp server port\n");
}


int main(int argc, char *argv[]) {
    int fd = -1;
    struct sockaddr_in sin;
    if (argc != 3) {
        usage(argv[0]);
        exit(1);
    }

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    int b_br = 1;
    setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &b_br, sizeof(b_br));
    

    bzero(&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(atoi(argv[2]));

    if (inet_pton(AF_INET, argv[1], (void *)&sin.sin_addr) != 1) {
        perror("inet_pton");
        exit(1);
    }

    char buf[BUFSIZ];
    while (1) {
        bzero(buf, BUFSIZ);
        if (fgets(buf, BUFSIZ-1, stdin) == NULL) {
            perror("fgets");
            continue;
        }

        sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&sin, sizeof(sin));
        if (!strncasecmp(buf, QUIT_STR, strlen(QUIT_STR))) {
            printf("Client is exiting!\n");
            break;
        }
    }
    close(fd);
    return 0;
}