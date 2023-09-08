#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>


#define KEY_ENTER 28

struct key_event {
    int code;
    int value;
};

int main(int argc, char *argv[]) {
    struct key_event ev;
    int ret;
    int fd;
    char in_buf[1024];

    fd = open("/dev/key0", O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    // while (1) {
    //     read(fd, &ev, sizeof(ev));
    //     if (ev.code == KEY_ENTER) {
    //         if (ev.value) {
    //             printf("key down\n");
    //         } else {
    //             printf("key up\n");
    //         }
    //     }
    // }

    struct pollfd fds[2];
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    fds[1].fd = fd;
    fds[1].events = POLLIN;

    while (1) {
        ret = poll(fds, 2, 5000);
        if (ret < 0) {
            perror("poll");
            exit(1);
        } else if (ret == 0) {
            printf("timeout\n");
        } else {
            if (fds[0].revents & POLLIN) {
                fgets(in_buf, sizeof(in_buf), stdin);
                printf("stdin: %s\n", in_buf);
            }
            if (fds[1].revents & POLLIN) {
                read(fd, &ev, sizeof(ev));
                if (ev.code == KEY_ENTER) {
                    if (ev.value) {
                        printf("key down\n");
                    } else {
                        printf("key up\n");
                    }
                }
            }
        }
    }
}

