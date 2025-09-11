#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct {
    int* buffer;
    int size;
} Task159;

void initTask(Task159* task, int size) {
    if (size <= 0) {
        fprintf(stderr, "Size must be greater than zero\n");
        exit(EXIT_FAILURE);
    }
    task->size = size;
    task->buffer = (int*)calloc(size, sizeof(int));
    if (!task->buffer) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
}

void freeTask(Task159* task) {
    free(task->buffer);
}

int readData(Task159* task, int index) {
    if (index < 0 || index >= task->size) {
        fprintf(stderr, "Invalid index\n");
        exit(EXIT_FAILURE);
    }
    return task->buffer[index];
}

int main() {
    Task159 task;
    initTask(&task, 10);
    task.buffer[0] = 100;
    task.buffer[1] = 200;
    task.buffer[2] = 300;
    task.buffer[3] = 400;
    task.buffer[4] = 500;

    printf("%d\n", readData(&task, 0));
    printf("%d\n", readData(&task, 1));
    printf("%d\n", readData(&task, 2));
    printf("%d\n", readData(&task, 3));
    printf("%d\n", readData(&task, 4));

    freeTask(&task);
    return 0;
}