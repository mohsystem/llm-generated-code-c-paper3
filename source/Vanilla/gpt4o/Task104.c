#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 5
#define STRING_SIZE 50

typedef struct {
    char buffer[BUFFER_SIZE][STRING_SIZE];
    int index;
} Task104;

void initBuffer(Task104 *task) {
    task->index = 0;
}

void addToBuffer(Task104 *task, const char *input) {
    if (task->index < BUFFER_SIZE) {
        strncpy(task->buffer[task->index], input, STRING_SIZE - 1);
        task->buffer[task->index][STRING_SIZE - 1] = '\0'; // Ensures null termination
        task->index++;
    } else {
        printf("Buffer is full\n");
    }
}

void printBuffer(const Task104 *task) {
    for (int i = 0; i < task->index; i++) {
        printf("%s\n", task->buffer[i]);
    }
}

int main() {
    Task104 task;
    initBuffer(&task);

    // Test cases
    addToBuffer(&task, "First");
    addToBuffer(&task, "Second");
    addToBuffer(&task, "Third");
    addToBuffer(&task, "Fourth");
    addToBuffer(&task, "Fifth");
    addToBuffer(&task, "Sixth"); // Should print "Buffer is full"

    printBuffer(&task);

    return 0;
}