#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


char *fmtname(char *path) {
    char *p;

    // Find first character after last slash.
    for (p=path+strlen(path); p>=path && *p!='/'; p--)
        ;
    p++;

    // // Return blank-padded name.
    // if (strlen(p) >= DIRSIZ)
    //     return p;
    return p;
}





void find(char *path, char *target) {
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch(st.type) {
        case T_FILE:
            if (!strcmp(fmtname(path), target)) {
                printf("%s\n", path);
            }
            break;
        case T_DIR:
            strcpy(buf, path);
            p = buf + strlen(buf);
            *p++ = '/';
            while (read(fd, &de, sizeof(de)) == sizeof(de)) {
                if (de.inum == 0)
                    continue;
                if (!strcmp(de.name, ".") || !strcmp(de.name, ".."))
                    continue;
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                if (stat(buf, &st) < 0) {
                    printf("find: cannot stat %s\n", buf);
                    continue;
                }
                find(buf, target);
            }
            break;
    }
    close(fd);
}



int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(2, "find: %s <path> <target>", argv[0]);
        exit(1);
    }

    find(argv[1], argv[2]);
    exit(0);
}