#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sched.h>

int
main(int argc, char *argv[]) {
    // measure system call
    int fd = open("./1.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU), nloops = 1000000;
    void *ptr = NULL;
    float read_sys_call, malloc_sys_call;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (size_t i = 0; i < nloops; i++) {
        read(fd, NULL, 0);
    }
    gettimeofday(&end, NULL);
    read_sys_call = (float) (end.tv_sec * 1000000 + end.tv_usec - start.tv_sec * 1000000 - start.tv_usec) / nloops;
    printf("read system call: %f microseconds\n\n", read_sys_call);
    gettimeofday(&start, NULL);
    for (size_t i = 0; i < nloops; i++) {
        ptr = malloc(1000);
    }
    gettimeofday(&end, NULL);
    malloc_sys_call = (float) (end.tv_sec * 1000000 + end.tv_usec - start.tv_sec * 1000000 - start.tv_usec) / nloops;
    printf("malloc system call: %f microseconds\n\n", malloc_sys_call);

    printf("read system call is %f times expensive than malloc system call\n", read_sys_call / malloc_sys_call);

    // below code would work on linux machines

    //measure context switch
    /*
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);

  int first_pipefd[2], second_pipefd[2];
    if (pipe(first_pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(second_pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t cpid = fork();

    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (cpid == 0) {    // child
        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
            exit(EXIT_FAILURE);
        }

        for (size_t i = 0; i < nloops; i++) {
            read(first_pipefd[0], NULL, 0);
            write(second_pipefd[1], NULL, 0);
        }
    } else {           // parent
        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
            exit(EXIT_FAILURE);
        }

        gettimeofday(&start, NULL);
        for (size_t i = 0; i < nloops; i++) {
            write(first_pipefd[1], NULL, 0);
            read(second_pipefd[0], NULL, 0);
        }
        gettimeofday(&end, NULL);
        printf("context switch: %f microseconds\n", (float) (end.tv_sec * 1000000 + end.tv_usec - start.tv_sec * 1000000 - start.tv_usec) / nloops);
    } */
    return 0;
}
