#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int panic(char *s) {
    fprintf(2, "%s\n", s);
    exit(1);
}

int fork1() {
    int pid;

    pid = fork();
    if (pid == -1) {
        panic("fork");
    }

    return pid;
    
}

int read1(int fd, char *buff, int size) {
    int ret;
    if ((ret = read(fd, buff, size)) < 0) {
        panic("read");
    }
    return ret;
}


int write1(int fd, char *buff, int size) {
    int ret;
    if ((ret = write(fd, buff, size)) < 0) {
        panic("write");
    }
    return ret;
}

void handle_primes(int *p, int divisor) {
    
    
    if (pipe(p) < 0) {
        panic("pipe"); 
    }

    if (fork1() == 0) { // Child
        int num;
        int sub_pipe[2] = {-1, -1};

        close(p[1]);
        while (read1(p[0], (char*) &num, 4)) {

            // Drop or print
            if ( num % divisor == 0 ) {
                if (num / divisor == 1) {
                    fprintf(1, "prime %d\n", num);
                }
                continue;
            }

            // Send to next
            if (sub_pipe[0] == -1) {
                handle_primes(sub_pipe, num);
            } 
            write1(sub_pipe[1], (char*) &num, 4);
            
        }
        close(p[0]);
        close(sub_pipe[1]);
        wait(0);
        exit(0);
    }

    // Parent
    close(p[0]);

}



int main() {
    int p[2];

    handle_primes(p, 2);

    for (int i = 0; i < 34; i++) {
        int temp = i + 2;
        write1(p[1], (char*) &temp, 4);
    }
    close(p[1]);
    
    wait(0);
    exit(0);

}
