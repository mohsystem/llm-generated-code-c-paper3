
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* buffer;
    size_t size;
} Task159;

bool initializeBuffer(Task159* task, size_t size) {
    if (size == 0) {
        return false;
    }
    
    task->buffer = (int*)malloc(size * sizeof(int));
    if (task->buffer == NULL) {
        return false;
    }
    
    task->size = size;
    
    // Initialize buffer with values
    for (size_t i = 0; i < size; i++) {
        task->buffer[i] = (int)(i + 1);
    }
    
    return true;
}

bool readFromBuffer(const Task159* task, size_t index, int* result) {
    if (task == NULL || task->buffer == NULL || result == NULL) {
        return false;
    }
    
    if (index >= task->size) {
        return false;
    }
    
    *result = task->buffer[index];
    return true;
}

void freeBuffer(Task159* task) {
    if (task != NULL && task->buffer != NULL) {
        free(task->buffer);
        task->buffer = NULL;
        task->size = 0;
    }
}

int main() {
    Task159 test = {NULL, 0};
    int result;
    
    // Test case 1: Initialize buffer
    if (!initializeBuffer(&test, 10)) {
        printf("Error: Failed to initialize buffer\\n");
        return 1;
    }
    
    // Test case 2: Valid index
    if (readFromBuffer(&test, 5, &result)) {
        printf("Test 1: %d\\n", result); // Should print 6
    } else {
        printf("Test 1: Invalid index\\n");
    }
    
    // Test case 3: Another valid index
    if (readFromBuffer(&test, 0, &result)) {
        printf("Test 2: %d\\n", result); // Should print 1
    } else {
        printf("Test 2: Invalid index\\n");
    }
    
    // Test case 4: Index at boundary
    if (readFromBuffer(&test, 9, &result)) {
        printf("Test 3: %d\\n", result); // Should print 10
    } else {
        printf("Test 3: Invalid index\\n");
    }
    
    // Test case 5: Invalid index
    if (readFromBuffer(&test, 10, &result)) {
        printf("Test 4: %d\\n", result);
    } else {
        printf("Test 4: Invalid index\\n");
    }
    
    // Cleanup
    freeBuffer(&test);
    return 0;
}
