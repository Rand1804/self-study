#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

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
} MSG;

int do_register(int sockfd, MSG *msg);
int do_login(int sockfd, MSG *msg);
void do_query(int sockfd, MSG *msg);
void do_history(int sockfd, MSG *msg);

int main(int argc, const char *argv[]) {
    int sockfd;
    struct sockaddr_in sin;
    int n;
    MSG msg;

    if (argc != 3) {
        printf("Usage:%s <serverip> <port>\n", argv[0]);
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    bzero(&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(argv[1]);
    sin.sin_port = htons(atoi(argv[2]));
    
    if (connect(sockfd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("connect");
        exit(1);
    }

    while(1) {
        printf("******************************************\n");
        printf("* 1.register    2.login    3.quit *\n");
        printf("******************************************\n");
        printf("Please choose:");
        scanf("%d", &n);
        getchar();

        switch (n)
        {
        case 1:
            do_register(sockfd, &msg);
            break;
        case 2:
            if (do_login(sockfd, &msg) == 1) {
                goto next;
            };
            break;
        case 3:
            close(sockfd);
            exit(0);
        
        default:
            printf("Invalid option.\n");
            break;
        }

    }

next:
    while(1) {
        printf("******************************************\n");
        printf("* 1.query_word  2.history   3.quit *\n");
        printf("******************************************\n");
        printf("Please choose:");
        scanf("%d", &n);
        getchar();

        switch (n) {
            case 1:
                do_query(sockfd, &msg);
                break;
            case 2:
                do_history(sockfd, &msg);
                break;
            case 3:
                close(sockfd);
                exit(0);
            
            default:
                printf("Invalid option.\n");
                break;
        }
    }

    return 0;
}

int do_register(int sockfd, MSG *msg) {
    printf("register ...\n");
    msg->type = R;
    printf("Input name:");
    scanf("%s", msg->name);
    // getchar();
    printf("Input password:");
    scanf("%s", msg->data);

    if (send(sockfd, msg, sizeof(MSG), 0) < 0) {
        perror("send");
        return -1;
    }

    if (recv(sockfd, msg, sizeof(MSG), 0) < 0) {
        perror("recv");
        return -1;
    }

    printf("%s\n", msg->data);
    return 0;
}

int do_login(int sockfd, MSG *msg) {
    printf("login ...\n");
    msg->type = L;
    printf("Input name:");
    scanf("%s", msg->name);
    // getchar();
    printf("Input password:");
    scanf("%s", msg->data);
    if (send(sockfd, msg, sizeof(MSG), 0) < 0) {
        perror("send");
        return -1;
    }

    if (recv(sockfd, msg, sizeof(MSG), 0) < 0) {
        perror("recv");
        return -1;
    }

    if (strncasecmp(msg->data, "OK", 2) == 0) {
        printf("Login success!\n");
        return 1;
    }

    printf("%s\n", msg->data);

    return 0;

}

void do_query(int sockfd, MSG *msg) {
    printf("query ...\n");
    msg->type = Q;
    puts("-------------------------");

    while(1) {
        printf("Input word:");
        scanf("%s", msg->data);
        if(!strncmp(msg->data, "#", 1)) {
            break;
        }
        if (send(sockfd, msg, sizeof(MSG), 0) < 0) {
            perror("send");
            return;
        }

        if (recv(sockfd, msg, sizeof(MSG), 0) < 0) {
            perror("recv");
            return;
        }
        printf("%s\n", msg->data);
    }

}

void do_history(int sockfd, MSG *msg) {
    printf("history ...\n");


}