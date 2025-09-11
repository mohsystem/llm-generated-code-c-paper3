#include <stdio.h>
#include <stdlib.h>

void* allocateMemory(int size) {
    return malloc(size);
}

void deallocateMemory(void* ptr) {
    free(ptr);
}

int main() {
    // Test cases
    for (int i = 0; i < 5; i++) {
        int size = i * 10 + 10;
        void* ptr = allocateMemory(size);
        printf("Allocated %d bytes\n", size);
        deallocateMemory(ptr);
        printf("Deallocated %d bytes\n", size);
    }
    return 0;
}