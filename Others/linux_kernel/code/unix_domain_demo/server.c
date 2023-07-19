#include "net.h"
#include <sys/un.h>

void* cli_data_handle(void *arg);

int main(void) {
    int fd = -1;

    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    int b_reuse = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &b_reuse, sizeof(int));
#if 0
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
#else
    struct sockaddr_un sun;
    bzero(&sun, sizeof(sun));
    sun.sun_family = AF_UNIX;

    /* if UNIX_DOMAIN_FILE exists, delete it */
    if (!access(UNIX_DOMAIN_FILE, F_OK)) {
        unlink(UNIX_DOMAIN_FILE);
    }
    strncpy(sun.sun_path, UNIX_DOMAIN_FILE, sizeof(sun.sun_path) - 1);


#endif
    if (bind(fd, (struct sockaddr *) &sun, sizeof(sun)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(fd, BACKLOG) < 0) {
        perror("listen");
        exit(1);
    }

    int newfd = -1;


    pthread_t tid;


    while (1) {
        if (newfd = accept(fd, NULL, NULL) < 0) {
            perror("accept");
            exit(1);
        }


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

