#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
 #include <signal.h>

struct key_event{
	int code;
	int value;
};

#define KEY_ENTER		28

static int fd;
static struct key_event event;

static void sigio_handler(int signo) {
    int ret;

    ret = read(fd, &event, sizeof(event));
    if (ret < 0) {
        perror("read");
        exit(1);
    }
    if (event.code == KEY_ENTER) {
        if (event.value) {
            printf("key down\n");
        } else {
            printf("key up\n");
        }
    }
}


int main(int argc, char *argv[]) {
    int ret;
    int flags;

    fd = open("/dev/key0", O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    signal(SIGIO, sigio_handler);
    fcntl(fd, F_SETOWN, getpid());
    flags = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, flags | FASYNC);

    while (1) {
        printf("I am waiting.....");
        sleep(3);
    }

    close(fd);
    return 0;

}