#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* keyName;
    char* keyValue;
} KeyValue;

typedef struct {
    KeyValue* keys;
    int size;
    int capacity;
} Task134;

Task134* createTask134() {
    Task134* task = malloc(sizeof(Task134));
    task->size = 0;
    task->capacity = 10;
    task->keys = malloc(sizeof(KeyValue) * task->capacity);
    return task;
}

void addKey(Task134* task, char* keyName, char* keyValue) {
    if (task->size == task->capacity) {
        task->capacity *= 2;
        task->keys = realloc(task->keys, sizeof(KeyValue) * task->capacity);
    }
    KeyValue kv;
    kv.keyName = strdup(keyName);
    kv.keyValue = strdup(keyValue);
    task->keys[task->size++] = kv;
}

char* getKey(Task134* task, char* keyName) {
    for (int i = 0; i < task->size; i++) {
        if (strcmp(task->keys[i].keyName, keyName) == 0) {
            return task->keys[i].keyValue;
        }
    }
    return NULL;
}

void removeKey(Task134* task, char* keyName) {
    for (int i = 0; i < task->size; i++) {
        if (strcmp(task->keys[i].keyName, keyName) == 0) {
            free(task->keys[i].keyName);
            free(task->keys[i].keyValue);
            memmove(task->keys + i, task->keys + i + 1, sizeof(KeyValue) * (task->size - i - 1));
            task->size--;
            return;
        }
    }
}

int main() {
    Task134* keyManager = createTask134();
    addKey(keyManager, "key1", "value1");
    addKey(keyManager, "key2", "value2");
    printf("%s\n", getKey(keyManager, "key1")); // prints: value1
    removeKey(keyManager, "key1");
    printf("%s\n", getKey(keyManager, "key1")); // prints: (nothing)
    return 0;
}