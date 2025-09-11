#include <stdio.h>
#include <stdlib.h>

void dynamicMemoryManagement(int size) {
    int* array = NULL;
    if (size > 0) {
        array = (int*)malloc(size * sizeof(int));
        if (array == NULL) {
            printf("Error: Not enough memory available.\n");
            return;
        }
        for (int i = 0; i < size; ++i) {
            array[i] = i;
        }
        free(array); // Deallocate memory
    }
}

int main() {
    dynamicMemoryManagement(5);
    dynamicMemoryManagement(10);
    dynamicMemoryManagement(0);
    dynamicMemoryManagement(-1);
    dynamicMemoryManagement(1000000);
    return 0;
}