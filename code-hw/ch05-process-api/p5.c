//
// Created by Dhruv Mohindru on 5/1/22.
//

//
// Created by Dhruv Mohindru on 4/1/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("hello\n");
        printf("Child process: child process id: %d\n", (int)getpid());
        printf("Child process: return value of wait(): %d\n", wait(NULL));
    } else {
        // parent goes down this path (original process)
        int wc = wait(NULL);
        printf("Parent process: wait returned: %d\n", wc);
        printf("Parent process: parent process id: %d\n", (int)getpid());

    }
    return 0;
}


