#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* key;
    char* value;
    struct Node* next;
} Node;

typedef struct {
    Node** buckets;
    int size;
    int capacity;
} HashTable;

int hash(HashTable* hashTable, const char* key) {
    int hash = 0;
    for (int i = 0; i < strlen(key); i++) {
        hash = (hash + key[i]) % hashTable->capacity;
    }
    return hash;
}

void insert(HashTable* hashTable, const char* key, const char* value) {
    if (key == NULL || value == NULL) {
        fprintf(stderr, "Key and value cannot be null\n");
        return;
    }
    Node* node = malloc(sizeof(Node));
    node->key = strdup(key);
    node->value = strdup(value);
    node->next = NULL;
    int index = hash(hashTable, key);
    Node* current = hashTable->buckets[index];
    if (current == NULL) {
        hashTable->buckets[index] = node;
    } else {
        while (current->next != NULL) {
            if (strcmp(current->key, key) == 0) {
                free(current->value);
                current->value = strdup(value);
                free(node->key);
                free(node->value);
                free(node);
                return;
            }
            current = current->next;
        }
        if (strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = strdup(value);
        } else {
            current->next = node;
        }
    }
    hashTable->size++;
}

char* search(HashTable* hashTable, const char* key) {
    if (key == NULL) {
        fprintf(stderr, "Key cannot be null\n");
        return NULL;
    }
    int index = hash(hashTable, key);
    Node* current = hashTable->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void deleteNode(HashTable* hashTable, const char* key) {
    if (key == NULL) {
        fprintf(stderr, "Key cannot be null\n");
        return;
    }
    int index = hash(hashTable, key);
    Node* current = hashTable->buckets[index];
    Node* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                hashTable->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
            hashTable->size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

int main() {
    HashTable hashTable;
    hashTable.capacity = 10;
    hashTable.size = 0;
    hashTable.buckets = calloc(hashTable.capacity, sizeof(Node*));
    insert(&hashTable, "key1", "value1");
    insert(&hashTable, "key2", "value2");
    insert(&hashTable, "key3", "value3");
    printf("%s\n", search(&hashTable, "key2")); // value2
    deleteNode(&hashTable, "key2");
    printf("%s\n", search(&hashTable, "key2")); // (null)
    return 0;
}