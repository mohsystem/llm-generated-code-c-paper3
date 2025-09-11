
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t* buffer;
    size_t size;
} Task159;

// Initialize buffer
bool init_buffer(Task159* task, size_t size) {
    if (size == 0) {
        return false;
    }
    
    task->buffer = (uint8_t*)calloc(size, sizeof(uint8_t));
    if (task->buffer == NULL) {
        return false;
    }
    
    task->size = size;
    return true;
}

// Read from buffer with bounds checking
bool read_from_buffer(const Task159* task, size_t index, uint8_t* value) {
    if (task == NULL || task->buffer == NULL || index >= task->size || value == NULL) {
        return false;
    }
    
    *value = task->buffer[index];
    return true;
}

// Write to buffer with bounds checking
bool write_to_buffer(Task159* task, size_t index, uint8_t value) {
    if (task == NULL || task->buffer == NULL || index >= task->size) {
        return false;
    }
    
    task->buffer[index] = value;
    return true;
}

// Free buffer
void free_buffer(Task159* task) {
    if (task != NULL && task->buffer != NULL) {
        free(task->buffer);
        task->buffer = NULL;
        task->size = 0;
    }
}

int main() {
    Task159 task;
    uint8_t value;
    
    // Test case 1: Initialize buffer and write/read valid index
    if (init_buffer(&task, 10)) {
        if (write_to_buffer(&task, 0, 65) && read_from_buffer(&task, 0, &value)) {
            printf("Test 1: %d\\n", value);
        }
    }
    
    // Test case 2: Write/read from valid index
    if (write_to_buffer(&task, 5, 90) && read_from_buffer(&task, 5, &value)) {
        printf("Test 2: %d\\n", value);
    }
    
    // Test case 3: Try negative index (will be converted to very large number)
    if (!read_from_buffer(&task, -1, &value)) {
        printf("Test 3: Caught invalid index access\\n");
    }
    
    // Test case 4: Try index beyond buffer size
    if (!read_from_buffer(&task, 10, &value)) {
        printf("Test 4: Caught out of bounds access\\n");
    }
    
    // Test case 5: Try creating buffer with zero size
    Task159 invalid_task;
    if (!init_buffer(&invalid_task, 0)) {
        printf("Test 5: Caught invalid buffer size\\n");
    }
    
    // Clean up
    free_buffer(&task);
    
    return 0;
}
