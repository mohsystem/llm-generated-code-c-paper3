#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValue {
    char *key;
    char *value;
    struct KeyValue *next;
} KeyValue;

KeyValue *keys = NULL;

void addKey(char *keyName, char *keyValue) {
    KeyValue *newNode = malloc(sizeof(KeyValue));
    newNode->key = strdup(keyName);
    newNode->value = strdup(keyValue);
    newNode->next = keys;
    keys = newNode;
}

char *getKey(char *keyName) {
    KeyValue *current = keys;
    while (current != NULL) {
        if (strcmp(current->key, keyName) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void removeKey(char *keyName) {
    KeyValue *temp = keys, *prev;
    if (temp != NULL && strcmp(temp->key, keyName) == 0) {
        keys = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && strcmp(temp->key, keyName) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    prev->next = temp->next;
    free(temp);
}

int main() {
    addKey("key1", "value1");
    addKey("key2", "value2");
    printf("%s\n", getKey("key1"));
    removeKey("key1");
    printf("%s\n", getKey("key1"));
    return 0;
}