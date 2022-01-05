//
// Created by Dhruv Mohindru on 5/1/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>
/**
Steps for this problem
 1. Parent process swaps two child process
 2. Parent should wait for both the process to finish
 3. First child process to write to std in of second process
 4. Second child process to read from standard input
 */

int
main(int argc, char *argv[])
{
    // redirect standard output to a file

    int fds[2];
    pipe(fds);

    int rc1 = fork();
    if (rc1 < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed for any one process\n");
        exit(1);
    } else if (rc1 == 0) {
        // First child
        // close read end of pipe
        close(fds[0]);
        if (fds[1] != STDOUT_FILENO) {
            dup2(fds[1], STDOUT_FILENO);
            close(fds[1]);
        }
        printf("hello, I am first child (pid:%d)\n", (int) getpid());
    }
    else {
        int rc2 = fork();
        if (rc2 < 0) {
            // fork failed; exit
            fprintf(stderr, "fork failed for any one process\n");
            exit(1);
        }
        else if (rc2 == 0) {
            // Second child
            // close write end of pipe
            close(fds[1]);

            if (fds[0] != STDIN_FILENO) {
                dup2(fds[0], STDIN_FILENO);
                close(fds[0]);
            }

            char buff[100];
            read(STDIN_FILENO, buff, 100);
            printf("Second process: hello, I am second child (pid:%d)\n", (int) getpid());
            printf("Second process: Message from first child: %s", buff);


        } else {
            wait(NULL); // wait for 1st child to finish
            wait(NULL); // wait for 2nd child to finish
            printf("hello, I am parent of %d and %d (pid:%d)\n",
                   rc1, rc2, (int) getpid());

        }
    }
    return 0;
}

