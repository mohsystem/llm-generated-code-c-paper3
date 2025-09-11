#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Improved C version
int *allocateAndDeallocate(int size) {
    if (size <= 0) {
        return NULL;  // Return NULL for non-positive size
    }
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        return NULL; // Return NULL if allocation fails
    }
    memset(arr, 0, size * sizeof(int)); // Initialize the memory to 0

    free(arr); // Explicit deallocation
    arr = NULL; // Set pointer to NULL after free

    return NULL; // Return NULL to indicate deallocation

}

int main() {
    // Test cases
    allocateAndDeallocate(5);
    allocateAndDeallocate(10);
    allocateAndDeallocate(0); // Test with 0 size
    allocateAndDeallocate(-5); // Test with negative size
    allocateAndDeallocate(1); // Test with size 1
    return 0;
}