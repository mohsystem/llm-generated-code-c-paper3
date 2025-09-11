#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 16

typedef struct Entry {
    char *key;
    char *value;
    struct Entry *next;
} Entry;

typedef struct {
    Entry **table;
} HashTable;

unsigned int hash(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % INITIAL_SIZE;
}

HashTable *createHashTable() {
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    hashTable->table = (Entry **)malloc(INITIAL_SIZE * sizeof(Entry *));
    for (int i = 0; i < INITIAL_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

void insert(HashTable *hashTable, const char *key, const char *value) {
    unsigned int index = hash(key);
    Entry *newEntry = (Entry *)malloc(sizeof(Entry));
    newEntry->key = strdup(key);
    newEntry->value = strdup(value);
    newEntry->next = hashTable->table[index];
    hashTable->table[index] = newEntry;
}

char *search(HashTable *hashTable, const char *key) {
    unsigned int index = hash(key);
    Entry *entry = hashTable->table[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

void deleteEntry(HashTable *hashTable, const char *key) {
    unsigned int index = hash(key);
    Entry *entry = hashTable->table[index];
    Entry *prev = NULL;
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) {
                prev->next = entry->next;
            } else {
                hashTable->table[index] = entry->next;
            }
            free(entry->key);
            free(entry->value);
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

void freeHashTable(HashTable *hashTable) {
    for (int i = 0; i < INITIAL_SIZE; i++) {
        Entry *entry = hashTable->table[i];
        while (entry) {
            Entry *temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(hashTable->table);
    free(hashTable);
}

int main() {
    HashTable *hashTable = createHashTable();
    insert(hashTable, "key1", "value1");
    insert(hashTable, "key2", "value2");
    insert(hashTable, "key3", "value3");
    deleteEntry(hashTable, "key2");
    printf("%s\n", search(hashTable, "key1")); // value1
    printf("%s\n", search(hashTable, "key2")); // (null)
    printf("%s\n", search(hashTable, "key3")); // value3
    insert(hashTable, "key3", "value3_updated");
    printf("%s\n", search(hashTable, "key3")); // value3_updated
    freeHashTable(hashTable);
    return 0;
}