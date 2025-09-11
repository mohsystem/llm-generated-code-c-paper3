#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* buffer;
    size_t size;
} Task159;

Task159* createTask159(size_t size) {
    Task159* task = (Task159*)malloc(sizeof(Task159));
    task->buffer = (int*)malloc(size * sizeof(int));
    task->size = size;
    for (size_t i = 0; i < size; ++i) {
        task->buffer[i] = i;
    }
    return task;
}

int readFromBuffer(Task159* task, size_t index) {
    if (index < 0 || index >= task->size) {
        fprintf(stderr, "Invalid index\n");
        return -1;
    }
    return task->buffer[index];
}

void freeTask159(Task159* task) {
    free(task->buffer);
    free(task);
}

int main() {
    Task159* task = createTask159(10);
    int testIndexes[] = {0, 5, 9, -1, 10};
    for (int i = 0; i < 5; ++i) {
        int result = readFromBuffer(task, testIndexes[i]);
        if (result != -1) {
            printf("Value at index %d: %d\n", testIndexes[i], result);
        }
    }
    freeTask159(task);
    return 0;
}