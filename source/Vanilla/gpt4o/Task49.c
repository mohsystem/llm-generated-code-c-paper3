// Simple representation, no actual API or database connection
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **database;
    int size;
    int capacity;
} Task49;

void initTask49(Task49 *task) {
    task->capacity = 10;
    task->size = 0;
    task->database = (char **)malloc(task->capacity * sizeof(char *));
}

void storeUserData(Task49 *task, const char *userData) {
    if (task->size >= task->capacity) {
        task->capacity *= 2;
        task->database = (char **)realloc(task->database, task->capacity * sizeof(char *));
    }
    task->database[task->size] = strdup(userData);
    task->size++;
    printf("Data stored: %s\n", userData);
}

int main() {
    Task49 task;
    initTask49(&task);
    storeUserData(&task, "User1");
    storeUserData(&task, "User2");
    storeUserData(&task, "User3");
    storeUserData(&task, "User4");
    storeUserData(&task, "User5");
    return 0;
}