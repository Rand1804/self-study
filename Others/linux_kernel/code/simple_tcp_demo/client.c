#include "net.h"


int main() {
    int fd = -1;
    struct sockaddr_in sin;

    /* Create a socket descriptor */
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
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
        perror("inet_pton");
        exit(1);
    }
#endif

    if (connect(fd, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("connect");
        exit(1);
    }
        
    
    char buf[BUFSIZ];
    while(1) {
        bzero(buf, BUFSIZ);
        if(fgets(buf, BUFSIZ-1, stdin) == NULL)
            continue;
        write(fd, buf, strlen(buf));
        printf("%d", sizeof(QUIT_STR));
        if (!strncasecmp(buf, QUIT_STR, sizeof(QUIT_STR)-1)) {
            printf("Client is exiting!\n");
            break;
        }
    }

    close(fd);
    return 0;

}
