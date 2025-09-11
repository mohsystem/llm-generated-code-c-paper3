#include <stdio.h>
#include <stdlib.h>

int* allocateMemory(int size) {
    if (size <= 0) {
        return NULL;
    }
    int* array = (int*)malloc(size * sizeof(int));
    // Deallocation example (normally done when no longer needed)
    free(array);
    return NULL; // Return NULL to indicate deallocation
}

int main() {
    // Test cases
    printf("Allocated memory: %p\n", allocateMemory(5));
    printf("Allocated memory: %p\n", allocateMemory(10));
    printf("Allocated memory: %p\n", allocateMemory(0));
    printf("Allocated memory: %p\n", allocateMemory(7));
    printf("Allocated memory: %p\n", allocateMemory(3));
    return 0;
}