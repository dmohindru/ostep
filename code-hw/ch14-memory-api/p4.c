//
// Created by Dhruv Mohindru on 14/2/2022.
//

#include <stdio.h>
#include <stdlib.h>

void print_array_elements(int *array, int size);

int main (int argc, char *argv[]) {
    // allocate memory array for two arrays
    int size = 2;
    int *array = malloc(size * sizeof(int));
    // assign value to allocated array
    array[0] = -1;
    array[1] = 0;
    // display array elements
    print_array_elements(array, size);
    // now allocate memory for two more array elements
    size = 4;
    array = realloc(array, size * sizeof(int));
    // assign value to newly allocated array elements
    array[2] = 1;
    array[3] = 2;
    // display array elements
    print_array_elements(array, size);
    free(array);
    return 0;
}

void print_array_elements(int *array, int size) {
    printf("array elements: ");
    for (int i = 0; i < size; i++) {
        printf(" %d ", array[i]);
    }
    printf("\n");
}

