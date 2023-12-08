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

int main(int argc, char *argv[]) {
    char *p;
    char buf[512];
    char **new_argv;
    
    if (argc < 2) {
        panic("Usage: xargs <exec> <args>");
    }
    
    while (read(0, buf, 512) < 0) {
        
    }
    for (p = arg; *p; p++) {
        if (*p == '\n') {
            *p = '\0';
            new_argv = generate_argv(argc, argv, arg);
            if (fork1() == 0) { // Child
                exec(argv[1], new_argv);
                exit(1);
            }
            wait(0);
            free_argv(new_argv);
            arg = p + 1;
        }
    }

    new_argv = generate_argv(argc, argv, arg);
    if (fork1() == 0) { // Child
        exec(argv[1], new_argv);
        exit(1);
    }
    wait(0);
    free_argv(new_argv);

    exit(0);

}
