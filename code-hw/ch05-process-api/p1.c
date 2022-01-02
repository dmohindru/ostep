#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    int x = 100;
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        printf("Child process: Initial value of x in child process: %d\n", x);
        x+=100;
        printf("Child process: Child process updated value of x as x+=100\n");
        printf("Child process: Final value of x in child process: %d\n", x);
    } else {
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d)\n",
               rc, (int) getpid());
        printf("Parent process: Initial value of x in parent process: %d\n", x);
        x+=200;
        printf("Parent process: Parent process updated value of x as x+=200\n");
        printf("Parent process: Final value of x in parent process: %d\n", x);
    }
    return 0;
}
