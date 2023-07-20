#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#define N 32

#define R 1     //  user - register
#define L 2     //  user - login
#define Q 3     //  user - query
#define H 4     //  user - history

// communication information structure
typedef struct {
    int type;
    char name[N];
    char data[256];
}MSG;

int main(int argc, const char *argv[]) {
    int sockfd;
    struct sockaddr_in sin;

    if (argc != 3) {
        printf("Usage:%s <serverip> <port>\n", argv[0]);
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }
}