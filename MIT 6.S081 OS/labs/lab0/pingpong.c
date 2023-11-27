#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"



int panic(char *s) {
    fprintf(2, "%s\n", s);
    exit(1);
}

int forkl() {
    int pid;

    pid = fork();
    if (pid == -1) {
        panic(fork);
    }
    return pid;
}


int main() {
    int send_p[2];
    int rev_p[2];
    char buff[1];
    char byte_to_send = 'c';
    char *byte_to_sendp = &byte_to_send;
    int count = 0;

    if (pipe(send_p) < 0) {
        panic("pipe");
    }
    if (pipe(rev_p) < 0) {
        panic(pipe);
    }
    if (fork1() == 0) {
        close(send_p[1]);
        close(rev_p[0]);
        read(send_p[0], buff, 1);
        fprintf(1, "%d: received ping", getpid());
        write(rev_p[1], buff, 1);
        exit(0);
    }


    close(send_p[0]);
    close(rev_p[1]);
    write(send_p[1], byte_to_sendp, 1);
    read(rev_p[0], buff, 1);
    fprintf(1, "%d: received pong", getpid());

    wait(0);
    exit(0);
}