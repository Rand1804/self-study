#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#define KEY_ENTER 28

struct key_event {
    int code;
    int value;
};

int main(int argc, char *argv[]) {
    struct key_event ev;

    int fd = open("/dev/key0", O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    while (1) {
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

