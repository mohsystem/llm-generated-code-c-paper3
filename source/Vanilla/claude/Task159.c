
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char* buffer;
    int size;
} Task159;

Task159* createBuffer(int size) {
    Task159* task = (Task159*)malloc(sizeof(Task159));
    task->buffer = (unsigned char*)malloc(size);
    task->size = size;
    
    // Initialize buffer with some data
    for(int i = 0; i < size; i++) {
        task->buffer[i] = i;
    }
    return task;
}

int readFromBuffer(Task159* task, int index, unsigned char* result) {
    if(index < 0 || index >= task->size) {
        return 0;  // Error
    }
    *result = task->buffer[index];
    return 1;  // Success
}

void freeBuffer(Task159* task) {
    free(task->buffer);
    free(task);
}

int main() {
    Task159* task = createBuffer(100);
    unsigned char value;
    
    // Test case 1: Valid index
    if(readFromBuffer(task, 5, &value)) {
        printf("Value at index 5: %d\\n", value);
    } else {
        printf("Error: Invalid index\\n");
    }
    
    // Test case 2: Valid index
    if(readFromBuffer(task, 50, &value)) {
        printf("Value at index 50: %d\\n", value);
    } else {
        printf("Error: Invalid index\\n");
    }
    
    // Test case 3: Valid index
    if(readFromBuffer(task, 99, &value)) {
        printf("Value at index 99: %d\\n", value);
    } else {
        printf("Error: Invalid index\\n");
    }
    
    // Test case 4: Invalid index - negative
    if(readFromBuffer(task, -1, &value)) {
        printf("Value at index -1: %d\\n", value);
    } else {
        printf("Error: Invalid index\\n");
    }
    
    // Test case 5: Invalid index - out of bounds
    if(readFromBuffer(task, 100, &value)) {
        printf("Value at index 100: %d\\n", value);
    } else {
        printf("Error: Invalid index\\n");
    }
    
    freeBuffer(task);
    return 0;
}
