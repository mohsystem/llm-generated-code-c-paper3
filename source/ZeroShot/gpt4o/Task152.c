#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 10

typedef struct Entry {
    char *key;
    char *value;
    struct Entry *next;
} Entry;

typedef struct {
    Entry *table[CAPACITY];
} Task152;

unsigned int hash(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % CAPACITY;
}

Task152 *createHashTable() {
    Task152 *hashTable = malloc(sizeof(Task152));
    for (int i = 0; i < CAPACITY; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

void insert(Task152 *hashTable, const char *key, const char *value) {
    unsigned int index = hash(key);
    Entry *entry = hashTable->table[index];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = strdup(value);
            return;
        }
        entry = entry->next;
    }
    entry = malloc(sizeof(Entry));
    entry->key = strdup(key);
    entry->value = strdup(value);
    entry->next = hashTable->table[index];
    hashTable->table[index] = entry;
}

char *search(Task152 *hashTable, const char *key) {
    unsigned int index = hash(key);
    Entry *entry = hashTable->table[index];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

int deleteKey(Task152 *hashTable, const char *key) {
    unsigned int index = hash(key);
    Entry *entry = hashTable->table[index];
    Entry *prev = NULL;
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            if (prev == NULL) {
                hashTable->table[index] = entry->next;
            } else {
                prev->next = entry->next;
            }
            free(entry->key);
            free(entry->value);
            free(entry);
            return 1;
        }
        prev = entry;
        entry = entry->next;
    }
    return 0;
}

int main() {
    Task152 *hashTable = createHashTable();
    insert(hashTable, "key1", "value1");
    insert(hashTable, "key2", "value2");
    insert(hashTable, "key3", "value3");
    insert(hashTable, "key4", "value4");
    insert(hashTable, "key5", "value5");

    printf("%s\n", search(hashTable, "key1")); // value1
    printf("%s\n", search(hashTable, "key6")); // (null)

    deleteKey(hashTable, "key3");
    printf("%s\n", search(hashTable, "key3")); // (null)

    return 0;
}