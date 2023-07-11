#include "net.h"

void* cli_data_handle(void *arg);

int main(void) {
    int fd = -1;
    struct sockaddr_in sin;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    int b_reuse = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &b_reuse, sizeof(int));

    bzero(&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(SERV_PORT);
#if 1
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
#else
    if (inet_pton(AF_INET, SERV_IP_ADDR, (void *) &sin.sin_addr.s_addr) != 1) {
        perror("inet_pton");
        exit(1);
    }
#endif
    if (bind(fd, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(fd, BACKLOG) < 0) {
        perror("listen");
        exit(1);
    }

    int newfd = -1;

#if 0
    struct sockaddr_in cin;
    socklen_t addrlen = sizeof(cin);
    if (newfd = accept(fd, (struct sockaddr *) &cin, &addrlen) < 0) {
        perror("accept");
        exit(1);
    }

    char ipv4_addr[16];
    if (!inet_ntop(AF_INET, (void *)&cin.sin_addr.s_addr, ipv4_addr, sizeof(cin))) {
        perror("inet_ntop");
        exit(1);
    }

    printf("Client(%s:%d) is connected!", ipv4_addr, ntohs(sin.sin_port));
    


    int ret = 1;
    char buf[BUFSIZ];
    bzero(buf, BUFSIZ);
    while(1) {
        do {
            ret = read(newfd, buf, BUFSIZ-1);
        } while(ret <0 && EINTR == errno);
        if (ret < 0) {
            perror("read");
            exit(1);
        }

        // client closed
        if (!ret) {
            break;
        }

        printf("Receive data: %s", buf);

        if (!strncasecmp(buf, QUIT_STR, sizeof(QUIT_STR))) {
            printf("Client is exiting!\n");
            break;
        }
    }
    close(newfd);
    close(fd);

    return 0;
}
#else
    pthread_t tid;
    struct sockaddr_in cin;
    socklen_t addrlen = sizeof(cin);
    while (1) {
        if (newfd = accept(fd, (struct sockaddr *) &cin, &addrlen) < 0) {
            perror("accept");
            exit(1);
        }

        char ipv4_addr[16];
        if (!inet_ntop(AF_INET, (void *)&cin.sin_addr, ipv4_addr, sizeof(ipv4_addr))) {
            perror("inet_ntop");
            exit(1);
        }

        printf("Client(%s:%d) is connected!", ipv4_addr, ntohs(cin.sin_port));
        pthread_create(&tid, NULL, cli_data_handle, (void *)&newfd);
    }
    
    close(fd);
    return 0;
}

void* cli_data_handle(void *arg) {
    pthread_detach(pthread_self());

    int newfd = *(int *)arg;
    printf("handler thread: newfd = %d\n", newfd);

    int ret = 1;
    char buf[BUFSIZ];
    bzero(buf, BUFSIZ);
    while(1) {
        do {
            ret = read(newfd, buf, BUFSIZ-1);
        } while(ret <0 && EINTR == errno);
        if (ret < 0) {
            perror("read");
            exit(1);
        }

        // client closed
        if (!ret) {
            break;
        }

        printf("Receive data: %s", buf);

        if (!strncasecmp(buf, QUIT_STR, sizeof(QUIT_STR))) {
            printf("Client(fd=%d) is exiting!\n");
            break;
        }
    }
    close(newfd);

}

#endif
