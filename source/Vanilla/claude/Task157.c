
#include <stdio.h>
#include <stdlib.h>

void allocateMemory(int** array, int size) {
    *array = (int*)malloc(size * sizeof(int));
    if (*array != NULL) {
        for(int i = 0; i < size; i++) {
            (*array)[i] = i;
        }
    }
}

void deallocateMemory(int** array) {
    if (*array != NULL) {
        free(*array);
        *array = NULL;
    }
}

int main() {
    int* array;
    
    // Test case 1
    allocateMemory(&array, 5);
    deallocateMemory(&array);
    
    // Test case 2
    allocateMemory(&array, 10);
    deallocateMemory(&array);
    
    // Test case 3
    allocateMemory(&array, 0);
    deallocateMemory(&array);
    
    // Test case 4
    allocateMemory(&array, 100);
    deallocateMemory(&array);
    
    // Test case 5
    allocateMemory(&array, 1);
    deallocateMemory(&array);
    
    return 0;
}
