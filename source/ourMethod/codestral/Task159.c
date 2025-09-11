#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* buffer;
    int size;
} Task159;

Task159* createTask159(int size) {
    Task159* task = malloc(sizeof(Task159));
    if (task == NULL) {
        return NULL;
    }
    task->size = size;
    task->buffer = malloc(size * sizeof(int));
    if (task->buffer == NULL) {
        free(task);
        return NULL;
    }
    // initialize buffer here
    return task;
}

void destroyTask159(Task159* task) {
    free(task->buffer);
    free(task);
}

int read(Task159* task, int index) {
    if (index < 0 || index >= task->size) {
        fprintf(stderr, "Index is out of bounds.\n");
        exit(EXIT_FAILURE);
    }
    return task->buffer[index];
}

int main() {
    Task159* task = createTask159(10);
    if (task == NULL) {
        return EXIT_FAILURE;
    }
    // test cases
    printf("%d\n", read(task, 5)); // should print the 5th element
    read(task, 10); // should print an error message and exit
    destroyTask159(task);
    return EXIT_SUCCESS;
}