#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocate memory
    int* array = (int*)malloc(5 * sizeof(int));

    // Check if memory allocation was successful
    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Use the memory
    for (int i = 0; i < 5; i++) {
        array[i] = i;
    }

    // Deallocate memory
    free(array);

    return 0;
}