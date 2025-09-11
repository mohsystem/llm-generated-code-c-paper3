#include <stdio.h>
#include <stdlib.h>

void* allocateMemory(int size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    return ptr;
}

void deallocateMemory(void* ptr) {
    free(ptr);
    ptr = NULL;
}

int main() {
    // Test cases
    for (int i = 1; i <= 5; i++) {
        int* array = (int*)allocateMemory(i * 10 * sizeof(int));
        printf("Allocated memory for %d elements\n", i * 10);
        deallocateMemory(array);
        printf("Deallocated memory\n\n");
    }
    return 0;
}