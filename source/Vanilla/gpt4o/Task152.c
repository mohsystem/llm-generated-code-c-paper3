#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 10

typedef struct Entry {
    char *key;
    char *value;
    struct Entry *next;
} Entry;

typedef struct HashTable {
    Entry *table[CAPACITY];
} HashTable;

unsigned int hash(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % CAPACITY;
}

HashTable* create_table() {
    HashTable *hashTable = (HashTable*) malloc(sizeof(HashTable));
    for (int i = 0; i < CAPACITY; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

void insert(HashTable *hashTable, const char *key, const char *value) {
    unsigned int index = hash(key);
    Entry *newEntry = (Entry*) malloc(sizeof(Entry));
    newEntry->key = strdup(key);
    newEntry->value = strdup(value);
    newEntry->next = hashTable->table[index];
    hashTable->table[index] = newEntry;
}

char* search(HashTable *hashTable, const char *key) {
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

void delete_key(HashTable *hashTable, const char *key) {
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
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

int main() {
    HashTable *hashTable = create_table();

    insert(hashTable, "key1", "value1");
    insert(hashTable, "key2", "value2");
    insert(hashTable, "key3", "value3");
    insert(hashTable, "key4", "value4");
    insert(hashTable, "key5", "value5");

    printf("Search key1: %s\n", search(hashTable, "key1")); // value1
    printf("Search key3: %s\n", search(hashTable, "key3")); // value3

    delete_key(hashTable, "key2");
    printf("Search key2: %s\n", search(hashTable, "key2")); // NULL

    return 0;
}