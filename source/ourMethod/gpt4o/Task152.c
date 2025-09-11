#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct HashNode {
    char *key;
    int value;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode *table[TABLE_SIZE];
} HashTable;

unsigned int getHash(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % TABLE_SIZE;
}

HashTable *createHashTable() {
    HashTable *hashTable = malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

void insert(HashTable *hashTable, const char *key, int value) {
    unsigned int hashKey = getHash(key);
    HashNode *node = hashTable->table[hashKey];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            node->value = value;
            return;
        }
        node = node->next;
    }
    node = malloc(sizeof(HashNode));
    node->key = strdup(key);
    node->value = value;
    node->next = hashTable->table[hashKey];
    hashTable->table[hashKey] = node;
}

int deleteKey(HashTable *hashTable, const char *key) {
    unsigned int hashKey = getHash(key);
    HashNode *node = hashTable->table[hashKey];
    HashNode *prev = NULL;
    while (node) {
        if (strcmp(node->key, key) == 0) {
            if (prev) {
                prev->next = node->next;
            } else {
                hashTable->table[hashKey] = node->next;
            }
            free(node->key);
            free(node);
            return 1;
        }
        prev = node;
        node = node->next;
    }
    return 0;
}

int search(HashTable *hashTable, const char *key) {
    unsigned int hashKey = getHash(key);
    HashNode *node = hashTable->table[hashKey];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return -1;
}

void freeHashTable(HashTable *hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode *node = hashTable->table[i];
        while (node) {
            HashNode *next = node->next;
            free(node->key);
            free(node);
            node = next;
        }
    }
    free(hashTable);
}

int main() {
    HashTable *hashTable = createHashTable();
    insert(hashTable, "apple", 1);
    insert(hashTable, "banana", 2);
    insert(hashTable, "cherry", 3);
    insert(hashTable, "date", 4);
    insert(hashTable, "elderberry", 5);

    printf("Search 'apple': %d\n", search(hashTable, "apple")); // 1
    printf("Search 'banana': %d\n", search(hashTable, "banana")); // 2

    printf("Delete 'banana': %d\n", deleteKey(hashTable, "banana")); // 1
    printf("Search 'banana': %d\n", search(hashTable, "banana")); // -1

    printf("Delete 'banana' again: %d\n", deleteKey(hashTable, "banana")); // 0

    freeHashTable(hashTable);

    return 0;
}