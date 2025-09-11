#include <stdio.h>
#include <stdlib.h>

typedef struct Entry {
    int key;
    char* value;
    struct Entry* next;
} Entry;

typedef struct {
    Entry** entries;
    int size;
} HashTable;

HashTable* createHashTable(int size) {
    HashTable* table = malloc(sizeof(HashTable));
    table->entries = malloc(sizeof(Entry*) * size);
    table->size = size;
    for (int i = 0; i < size; i++) {
        table->entries[i] = NULL;
    }
    return table;
}

void insert(HashTable* table, int key, char* value) {
    int index = key % table->size;
    Entry* newEntry = malloc(sizeof(Entry));
    newEntry->key = key;
    newEntry->value = value;
    newEntry->next = table->entries[index];
    table->entries[index] = newEntry;
}

void deleteKey(HashTable* table, int key) {
    int index = key % table->size;
    Entry* entry = table->entries[index];
    Entry* prev = NULL;
    while (entry != NULL && entry->key != key) {
        prev = entry;
        entry = entry->next;
    }
    if (entry == NULL) {
        return;
    }
    if (prev == NULL) {
        table->entries[index] = entry->next;
    } else {
        prev->next = entry->next;
    }
    free(entry);
}

char* search(HashTable* table, int key) {
    int index = key % table->size;
    Entry* entry = table->entries[index];
    while (entry != NULL) {
        if (entry->key == key) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

int main() {
    HashTable* hashTable = createHashTable(10);
    insert(hashTable, 1, "One");
    insert(hashTable, 2, "Two");
    insert(hashTable, 3, "Three");
    printf("%s\n", search(hashTable, 2));  // Two
    deleteKey(hashTable, 2);
    printf("%s\n", search(hashTable, 2));  // (null)
    return 0;
}