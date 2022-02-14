//
// Created by Dhruv Mohindru on 14/2/2022.
//

#include <stdlib.h>
#include <stdio.h>


int main (int argc, char *argv[]) {
    int *array = malloc(100 * sizeof(int));
    array[0] = -1;
    free(array+50);
    printf("array[0]: %d\n", array[70]);

    return 0;
}

