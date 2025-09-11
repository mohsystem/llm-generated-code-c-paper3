#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 10

typedef struct Entry {
    int key;
    int value;
    struct Entry *next;
} Entry;

typedef struct Task152 {
    Entry **table;
} Task152;

Task152 *createHashTable() {
    Task152 *ht = (Task152 *)malloc(sizeof(Task152));
    if (ht == NULL) {
        return NULL;
    }
    ht->table = (Entry **)calloc(TABLE_SIZE, sizeof(Entry *));
    if (ht->table == NULL) {
        free(ht);
        return NULL;
    }
    return ht;
}

int hash(int key) {
    return key % TABLE_SIZE;
}

void insert(Task152 *ht, int key, int value) {
    int index = hash(key);
    Entry *newEntry = (Entry *)malloc(sizeof(Entry));
    if (newEntry == NULL) {
        return; // Handle memory allocation failure
    }

    newEntry->key = key;
    newEntry->value = value;
    newEntry->next = ht->table[index];
    ht->table[index] = newEntry;
}


int search(Task152 *ht, int key) {
    int index = hash(key);
    Entry *current = ht->table[index];
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1; // Return -1 to indicate not found
}

void deleteKey(Task152 *ht, int key) {
    int index = hash(key);
    Entry *current = ht->table[index];
    Entry *prev = NULL;

    while (current != NULL && current->key != key) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        return; // Key not found
    }

    if (prev == NULL) {
        ht->table[index] = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
}


void freeHashTable(Task152 *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry *current = ht->table[i];
        while (current != NULL) {
            Entry *next = current->next;
            free(current);
            current = next;
        }
    }
    free(ht->table);
    free(ht);
}

int main() {
    Task152 *ht = createHashTable();
    if (ht == NULL) {
        fprintf(stderr, "Failed to create hash table\n");
        return 1;
    }

    // Test cases
    insert(ht, 1, 10);
    insert(ht, 2, 20);
    insert(ht, 11, 110); // Collision with 1
    insert(ht, 22, 220);
    

    printf("Search 2: %d\n", search(ht, 2)); // Output: 20
    printf("Search 11: %d\n", search(ht, 11)); // Output: 110
    printf("Search 3: %d\n", search(ht, 3)); // Output: -1 (Not found)

    deleteKey(ht, 11);
    printf("Search 11 after deletion: %d\n", search(ht, 11)); // Output: -1 (Not found)
    printf("Search 1: %d\n", search(ht, 1)); // Output: 10
    
    insert(ht, 5, 50);
    insert(ht, 15, 150);
    printf("Search 15: %d\n", search(ht, 15)); // Output: 150
    printf("Search 5: %d\n", search(ht, 5)); // Output: 50

    freeHashTable(ht);
    return 0;
}