#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char *buffer;
    int size;
} Task159;

Task159* create_task159(int size) {
    Task159* task = (Task159*)malloc(sizeof(Task159));
    task->buffer = (unsigned char*)malloc(size * sizeof(unsigned char));
    task->size = size;
    for (int i = 0; i < size; i++) {
        task->buffer[i] = i; // Initializing with some data
    }
    return task;
}

unsigned char read_from_buffer(Task159* task, int index) {
    if (index < 0 || index >= task->size) {
        fprintf(stderr, "Error: Index out of bounds\n");
        exit(1);
    }
    return task->buffer[index];
}

void free_task159(Task159* task) {
    free(task->buffer);
    free(task);
}

int main() {
    Task159* task = create_task159(100); // Allocating buffer of size 100
    int testCases[] = {0, 50, 99, 100, -1}; // 5 test cases

    for (int i = 0; i < 5; i++) {
        int index = testCases[i];
        printf("Reading from index %d: ", index);
        if (index < 0 || index >= 100) {
            printf("Error: Index out of bounds\n");
        } else {
            printf("%d\n", read_from_buffer(task, index));
        }
    }

    free_task159(task);
    return 0;
}