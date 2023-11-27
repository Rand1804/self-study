#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * Total exchanges: 1000000
 * Total time (milliseconds): 27451
 * Exchanges per second: 36428.545408
*/

int main() {
    int pipe1[2], pipe2[2];
    char readbuffer;
    const char byteToSend = 'x';
    struct timeval start, end;
    long exchanges = 0, seconds = 0, useconds = 0;
    long max_exchanges = 1000000;

    // Create the two pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { 
        close(pipe1[1]); 
        close(pipe2[0]);

        while (read(pipe1[0], &readbuffer, 1) > 0) {
            write(pipe2[1], &readbuffer, 1);
        }

        close(pipe1[0]);
        close(pipe2[1]);
        exit(EXIT_SUCCESS);
    } else { // Parent process
        close(pipe1[0]);
        close(pipe2[1]); 

        gettimeofday(&start, NULL);
        for (long i = 0; i < max_exchanges; i++) {
            write(pipe1[1], &byteToSend, 1);
            read(pipe2[0], &readbuffer, 1);
        }
        gettimeofday(&end, NULL);

        seconds  = end.tv_sec  - start.tv_sec;
        useconds = end.tv_usec - start.tv_usec;
        long totalTime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
        printf("Total exchanges: %ld\n", max_exchanges);
        printf("Total time (milliseconds): %ld\n", totalTime);
        printf("Exchanges per second: %f\n", max_exchanges / (totalTime / 1000.0));

        close(pipe1[1]);
        close(pipe2[0]);
        wait(0);
    }

    return 0;
}
