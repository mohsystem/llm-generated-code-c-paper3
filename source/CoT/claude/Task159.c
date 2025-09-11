
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* buffer;
    int size;
} Task159;

bool initializeBuffer(Task159* task, int size) {
    if (size <= 0) {
        return false;
    }
    
    task->buffer = (int*)malloc(size * sizeof(int));
    if (task->buffer == NULL) {
        return false;
    }
    
    task->size = size;
    
    // Initialize buffer with data
    for(int i = 0; i < size; i++) {
        task->buffer[i] = i + 1;
    }
    return true;
}

bool readFromBuffer(Task159* task, int index, int* result) {
    if (task == NULL || task->buffer == NULL || result == NULL) {
        return false;
    }
    
    if (index < 0 || index >= task->size) {
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
    Task159 task;
    int result;
    
    // Initialize buffer
    if (!initializeBuffer(&task, 10)) {
        printf("Error: Failed to initialize buffer\\n");
        return 1;
    }
    
    // Test case 1: Valid index
    if (readFromBuffer(&task, 5, &result)) {
        printf("Test 1: %d\\n", result);
    } else {
        printf("Test 1: Error reading from buffer\\n");
    }
    
    // Test case 2: Another valid index
    if (readFromBuffer(&task, 0, &result)) {
        printf("Test 2: %d\\n", result);
    } else {
        printf("Test 2: Error reading from buffer\\n");
    }
    
    // Test case 3: Valid boundary index
    if (readFromBuffer(&task, 9, &result)) {
        printf("Test 3: %d\\n", result);
    } else {
        printf("Test 3: Error reading from buffer\\n");
    }
    
    // Test case 4: Invalid negative index
    if (readFromBuffer(&task, -1, &result)) {
        printf("Test 4: %d\\n", result);
    } else {
        printf("Test 4: Error reading from buffer\\n");
    }
    
    // Test case 5: Invalid out of bounds index
    if (readFromBuffer(&task, 10, &result)) {
        printf("Test 5: %d\\n", result);
    } else {
        printf("Test 5: Error reading from buffer\\n");
    }
    
    // Clean up
    freeBuffer(&task);
    
    return 0;
}
