#include <stdio.h>
#include <stdlib.h>

// Basic hash table implementation in C (limited functionality for demonstration)
// Note: This is a simplified example and doesn't handle collisions efficiently.

#define TABLE_SIZE 10

typedef struct {
    int key;
    int value;
    int occupied; // Flag to indicate if slot is occupied
} HashEntry;

typedef struct {
    HashEntry table[TABLE_SIZE];
} HashTable;

void insert(HashTable* ht, int key, int value) {
    int index = key % TABLE_SIZE;
    ht->table[index].key = key;
    ht->table[index].value = value;
    ht->table[index].occupied = 1;
}

void delete_key(HashTable* ht, int key) {
    int index = key % TABLE_SIZE;
    if (ht->table[index].occupied && ht->table[index].key == key) {
        ht->table[index].occupied = 0; // Mark as unoccupied
    }
}

int search(HashTable* ht, int key) {
    int index = key % TABLE_SIZE;
    if (ht->table[index].occupied && ht->table[index].key == key) {
        return ht->table[index].value;
    }
    return -1; // Return -1 if not found
}

int main() {
    HashTable ht;
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht.table[i].occupied = 0; // Initialize table
    }

    // Test cases
    insert(&ht, 1, 10);
    insert(&ht, 2, 20);
    insert(&ht, 3, 30);
    insert(&ht, 4, 40);
    insert(&ht, 5, 50);


    printf("%d\n", search(&ht, 2)); // Output: 20
    delete_key(&ht, 2);
    printf("%d\n", search(&ht, 2)); // Output: -1
    printf("%d\n", search(&ht, 4)); // Output: 40
    insert(&ht, 3, 35); // Update value
    printf("%d\n", search(&ht, 3)); // Output: 35
    printf("%d\n", search(&ht, 6)); // Output: -1

    return 0;
}