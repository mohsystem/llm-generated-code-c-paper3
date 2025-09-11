#include <stdio.h>
#include <stdlib.h>

void allocateDeallocate(int size) {
    // Allocate memory
    int* arr = (int*)malloc(size * sizeof(int));
    printf("Memory allocated for %d integers.\n", size);

    // Deallocate memory
    free(arr);
    printf("Memory deallocated.\n");
}

int main() {
    // Test cases
    allocateDeallocate(10);
    allocateDeallocate(20);
    allocateDeallocate(30);
    allocateDeallocate(40);
    allocateDeallocate(50);

    return 0;
}