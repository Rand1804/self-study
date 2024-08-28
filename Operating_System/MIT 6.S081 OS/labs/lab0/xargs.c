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

char **generate_argv(int argc, char *argv[], char *arg) {
    char **new_argv = malloc((argc+1) * sizeof *new_argv);
    uint size;

    for (int i = 1; i < argc; i++) {
        size = strlen(argv[i]) + 1;
        new_argv[i-1] = malloc(size);
        memmove(new_argv[i-1], argv[i], size);
    }
    size = strlen(arg) + 1;
    new_argv[argc-1] = malloc(size);
    memmove(new_argv[argc-1], arg, size);
    new_argv[argc] = 0;

    return new_argv;
}


void free_argv(char **argv) {
    for (int i = 0;argv[i]; i++) {
        free(argv[i]);
    }
    free(argv);
}

char fgetc(int fd) {
    char c;

    if (read(0, &c, 1) == 1) {
        return c;
    } else {
        return 0;
    }
}


int getline(char *buffer, int *buffer_sizep, int fd) {
    if (buffer == 0 || buffer_sizep == 0) {
        return -1;
    }

    uint i = 0;
    char c;

    while ((c=fgetc(fd)) != '\n' && c != 0) {
    
        if (i+1 >= *buffer_sizep) {
            *buffer_sizep *= 2;
            char *new_buffer  = (char*)malloc(*buffer_sizep);
            if (new_buffer == 0) {
                return -1;
            }
            free(buffer);
            buffer = new_buffer;
        }

        buffer[i++] = c;
    }

    if (i == 0 && c == 0) {
        return 1;
    }

    buffer[i] = 0;
    return 0;
}

void print_newargv(char **argv) {
    if (argv == 0) {
        panic("print_newargv");
    }
    for (int i = 0; argv[i]; i++) {
        printf("argv%d: %s\n", i, argv[i]);
    }
}


int main(int argc, char *argv[]) {
    char **new_argv;
    int buffer_size = 100;
    char *buffer = (char*) malloc(buffer_size);
    if (buffer == 0) {
        return 1;
    }

    if (argc < 2) {
        panic("Usage: xargs <exec> <args>");
    }
    
    while (getline(buffer, &buffer_size, 0) == 0) {
        new_argv = generate_argv(argc, argv, buffer);
        if (fork1() == 0) { // Child
            exec(argv[1], new_argv);
            exit(1);
        }
        wait(0);
        free_argv(new_argv);
    }


    free(buffer);

    exit(0);

}
