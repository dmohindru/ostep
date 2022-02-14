#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sched.h>

int
main(int argc, char *argv[]) {
    /*
     * 1. Check for number of command line argument. If less than 1 then display error and exit
     * 2. Allocate memory in MB
     * 3. Infinite Loop through this array setting its value to zero
     */

    if (argc < 2) {
        fprintf(stderr, "Usage: p1 <memory in megabytes>\n");
        return 1;
    }
    printf("PID of process: %d\n", getpid());
    printf("Allocating %s MB of memory\n", argv[1]);
    size_t bytes = atoi(argv[1]) * 1000000;
    size_t limit = bytes / sizeof (int);
    int *array = malloc(bytes);
    size_t i = 0;
    while (1) {
        array[i++] = 0;
        if (i == limit)
            i = 0;
    }
    return 0;
}
