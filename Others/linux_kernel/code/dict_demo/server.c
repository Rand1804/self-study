#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>

#include <sqlite3.h>

#define N 32

#define R 1     //  user - register
#define L 2     //  user - login
#define Q 3     //  user - query
#define H 4     //  user - history

#define DATABASE "/home/wuwt/code/self-study/Others/linux_kernel/code/dict_demo/my.db"

// communication information structure
typedef struct {
    int type;
    char name[N];
    char data[256];
} MSG;

void do_client(int acceptfd, sqlite3 *db);
void do_register(int acceptfd, MSG *msg, sqlite3 *db);
int do_login(int acceptfd, MSG *msg, sqlite3 *db);
void do_query(int acceptfd, MSG *msg, sqlite3 *db);
void do_history(int acceptfd, MSG *msg, sqlite3 *db);

int main(int argc, const char *argv[]) {
    int sockfd;
    struct sockaddr_in sin;
    int n;
    MSG msg;
    sqlite3 *db;
    int acceptfd;
    pid_t pid;

    if (sqlite3_open(DATABASE, &db) != SQLITE_OK) {
        printf("%s\n", sqlite3_errmsg(db));
        exit(1);
    }
    printf("Open DATABASE success\n");

    if (argc != 3) {
        printf("Usage:%s <serverip> <port>\n", argv[0]);
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    int b_reuse = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &b_reuse, sizeof(b_reuse));

    bzero(&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(argv[1]);
    sin.sin_port = htons(atoi(argv[2]));
    
    if(bind(sockfd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, 5) < 0) {
        perror("listen");
        exit(1);
    }

    signal(SIGCHLD, SIG_IGN);
    while(1) {
        if ((acceptfd = accept(sockfd, NULL, NULL)) < 0) {
            perror("accept");
            exit(1);
        }

        if ((pid = fork()) < 0) {
            perror("fork");
            exit(1);
        }

        if (pid == 0) { // child process
            close(sockfd);
            do_client(acceptfd, db);
            close(acceptfd);
            exit(0);
        }

        // parent process
        close(acceptfd);
    }

    return 0;
}

void do_client(int acceptfd, sqlite3 *db) {

    MSG msg;
    while(recv(acceptfd, &msg, sizeof(msg), 0) > 0) {
        switch (msg.type) {
            case R:
                do_register(acceptfd, &msg, db);
                break;
            case L:
                do_login(acceptfd, &msg, db);
                break;
            case Q:
                do_query(acceptfd, &msg, db);
                break;
            case H:
                do_history(acceptfd, &msg, db);
                break;
            
            default:
                printf("Invalid option.\n");
                break;
        }
    }

    printf("client exit.\n");

}

void do_register(int acceptfd, MSG *msg, sqlite3 *db) {
    char *errmsg;
    char sql[128];

    sprintf(sql, "insert into user values('%s', '%s');", msg->name, msg->data);

    if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK) {
        printf("%s\n", errmsg);
        strcpy(msg->data, "user name already exists.");
    } else {
        strcpy(msg->data, "OK!");
    }

    if (send(acceptfd, msg, sizeof(MSG), 0) < 0) {
        perror("fail to send");
        return;
    }
}

int do_login(int acceptfd, MSG *msg, sqlite3 *db){
    char sql[128] = {};
    char *errmsg;
    int nrow;
    int ncolumn;
    char **resultp;

    sprintf(sql, "select * from user where name = '%s' and pass = '%s';", msg->name, msg->data);

    if (sqlite3_get_table(db, sql, &resultp, &nrow, &ncolumn, &errmsg) != SQLITE_OK) {
        printf("%s\n", errmsg);
        return -1;
    }

    if (nrow == 1) {
        strcpy(msg->data, "OK!");
    } else {
        strcpy(msg->data, "Wrong user name or password");
    }

    send(acceptfd, msg, sizeof(MSG), 0);
    return 0;
}

int do_searchword(MSG *msg) {
    FILE *fp;
    char buf[512] = {};
    int len = strlen(msg->data);
    int result = 0;
    char *p;

    if ((fp = fopen("/home/wuwt/code/self-study/Others/linux_kernel/code/dict_demo/dict.txt", "r")) == NULL) {
        perror("Fail to fopen.\n");
        strcpy(msg->data, "Fail to open dict.txt");
        return -1;
    }

    printf("%s, len = %d\n", msg->data, len);

    while (fgets(buf, 512, fp) != NULL) {
        if (strcmp(buf, "\n") == 0) {
            continue;
        }

        result = strncmp(buf, msg->data, len);

        if (result < 0) {
            continue;
        }
        if (result > 0) {
            strcpy(msg->data, "NOT FOUND!");
            printf("%s\n", buf);
            break;
        }
        if (result == 0 && buf[len]!=' ') {
            strcpy(msg->data, "NOT FOUND!");
            printf("%s\n", buf);
            break;
        }

        p = buf + len;
        while (*p == ' ') {
            p++;
        }
        strcpy(msg->data, p);
        break;
        
    }
    fclose(fp);

    return 0;

}

int get_date(char *date) {
    time_t t;
    struct tm *tp;
    time(&t);
    tp = localtime(&t);

    sprintf(date, "%d-%d-%d %d:%d:%d",
        tp->tm_year+1900, 
        tp->tm_mon+1, 
        tp->tm_mday,
        tp->tm_hour,
        tp->tm_min,
        tp->tm_sec
    );
    return 0;
}

void do_query(int acceptfd, MSG *msg, sqlite3 *db) {
    char word[128];
    char sql[128];
    char date[256];
    char *errmsg;
    int result;

    strcpy(word, msg->data);
    result = do_searchword(msg);
    send(acceptfd, msg, sizeof(MSG), 0);
    if (result == 0) {
        get_date(date);
        sprintf(sql, "insert into record values('%s', '%s', '%s');", msg->name, date, word);
        if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK) {
            printf("%s\n", errmsg);
            return;
        }
    }
    
    return;
}

int history_callback(void *arg, int f_num, char **f_value, char **f_name) {
    int acceptfd = (int)arg;
    MSG msg;

    sprintf(msg.data, "%s %s", f_value[1], f_value[2]);
    if (send(acceptfd, &msg, sizeof(MSG), 0) < 0) {
        perror("send");
        return -1;
    }

    return 0;
}


void do_history(int acceptfd, MSG *msg, sqlite3 *db) {
    char sql[128];
    char *errmsg;

    sprintf(sql, "select * from record where name = '%s';", msg->name);

    if (sqlite3_exec(db, sql, history_callback, (void *)acceptfd, &errmsg) != SQLITE_OK) {
        printf("%s\n", errmsg);
        return;
    }

    msg->data[0] = '\0';
    send(acceptfd, msg, sizeof(MSG), 0);
    return;
}