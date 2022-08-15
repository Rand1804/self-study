#include <unistd.h>
#include <stdio.h>

int main (int argc, char** argv) {
    int opt, x, y;
    printf("%d, %s\n", argc, *argv + 1);
    /* looping over arguments */
    while (-1 != (opt = getopt(argc, argv, "x:y:"))) {
        /* determine which argument it's processing */
        printf("%d", opt);
        switch (opt) {
            case 'x':
                x = atoi(optarg);
                printf("x:%d\n", x);
                break;
            case 'y':
                y = atoi(optarg);
                printf("y:%d", y);
                break;
            default:
                printf("wrong argument\n");
                break;
        }
    }
}