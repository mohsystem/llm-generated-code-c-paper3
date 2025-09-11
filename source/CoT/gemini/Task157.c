#include <stdio.h>
#include <stdlib.h>

void allocateAndDeallocate() {
    // Allocate memory dynamically
    int* ptr = (int*)malloc(10 * sizeof(int));

    // Check if allocation was successful
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1); // Exit with error code
    }

    // Use the allocated memory (example)
    for (int i = 0; i < 10; i++) {
        ptr[i] = i * 5;
    }

    // Deallocate the memory
    free(ptr);
    ptr = NULL; // Set pointer to null to prevent dangling pointers
}

int main() {
    for (int i = 0; i < 5; i++) {
        allocateAndDeallocate();
        printf("Memory allocated and deallocated (Test case %d)\n", i + 1);
    }
    return 0;
}