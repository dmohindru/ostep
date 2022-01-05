//
// Created by Dhruv Mohindru on 4/1/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
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

        // now exec "/bin/ls"...
        char *myargs[3];
        myargs[0] = strdup("/bin/ls");   // program: "ls" (word count)
        myargs[1] = NULL;           // marks end of array
        printf("running ls with execvp....\n");
        execvp(myargs[0], myargs);  // runs ls program
    } else {
        // parent goes down this path (original process)
        int wc = wait(NULL);
        assert(wc >= 0);
        printf("good bye from parent\n");
    }
    return 0;
}

