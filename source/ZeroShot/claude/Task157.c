
#include <stdio.h>
#include <stdlib.h>

void* allocateMemory(size_t size) {
    void* ptr = NULL;
    if (size > 0) {
        ptr = malloc(size);
        if (ptr == NULL) {
            printf("Memory allocation failed\\n");
        }
    }
    return ptr;
}

void deallocateMemory(void* ptr) {
    if (ptr != NULL) {
        free(ptr);
    }
}

int main() {
    int* ptr;
    
    // Test case 1: Allocate and deallocate small array
    ptr = (int*)allocateMemory(10 * sizeof(int));
    deallocateMemory(ptr);
    
    // Test case 2: Allocate and deallocate medium array
    ptr = (int*)allocateMemory(1000 * sizeof(int));
    deallocateMemory(ptr);
    
    // Test case 3: Allocate and deallocate large array
    ptr = (int*)allocateMemory(100000 * sizeof(int));
    deallocateMemory(ptr);
    
    // Test case 4: Try to allocate very large array
    ptr = (int*)allocateMemory(SIZE_MAX);
    deallocateMemory(ptr);
    
    // Test case 5: Allocate zero size array
    ptr = (int*)allocateMemory(0);
    deallocateMemory(ptr);
    
    return 0;
}
