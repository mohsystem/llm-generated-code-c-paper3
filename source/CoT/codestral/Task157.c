// Task157.c
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocate memory
    int* numbers = (int*)malloc(5 * sizeof(int));

    // Use the memory
    for (int i = 0; i < 5; i++) {
        numbers[i] = i;
    }

    // Deallocate memory
    free(numbers);
    return 0;
}