#include <stdio.h>
#include <stdlib.h>

typedef struct HashTable {
    int size;
    int* table;
} HashTable;

HashTable* createHashTable(int size) {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->size = size;
    hashTable->table = (int*)calloc(size, sizeof(int));
    for (int i = 0; i < size; i++) {
        hashTable->table[i] = -1;
    }
    return hashTable;
}

int hashFunction(HashTable* hashTable, int key) {
    return key % hashTable->size;
}

void insertItem(HashTable* hashTable, int key) {
    int index = hashFunction(hashTable, key);
    if (hashTable->table[index] == -1) {
        hashTable->table[index] = key;
    } else {
        printf("Collision: Unable to insert %d\n", key);
    }
}

void deleteItem(HashTable* hashTable, int key) {
    int index = hashFunction(hashTable, key);
    if (hashTable->table[index] == key) {
        hashTable->table[index] = -1;
    } else {
        printf("%d not present in the hash table\n", key);
    }
}

void searchItem(HashTable* hashTable, int key) {
    int index = hashFunction(hashTable, key);
    if (hashTable->table[index] == key) {
        printf("Search Found\n");
    } else {
        printf("Search Not Found\n");
    }
}

void displayHash(HashTable* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        printf("table[%d] = %d\n", i, hashTable->table[i]);
    }
}

void freeHashTable(HashTable* hashTable) {
    free(hashTable->table);
    free(hashTable);
}

void mainFunction() {
    HashTable* hashTable = createHashTable(7);
    insertItem(hashTable, 10);
    insertItem(hashTable, 4);
    insertItem(hashTable, 2);
    insertItem(hashTable, 3);
    displayHash(hashTable);
    printf("Deleting value 10..\n");
    deleteItem(hashTable, 10);
    displayHash(hashTable);
    printf("Deleting value 5..\n");
    deleteItem(hashTable, 5);
    displayHash(hashTable);
    printf("Searching value 4..\n");
    searchItem(hashTable, 4);
    printf("Searching value 10..\n");
    searchItem(hashTable, 10);
    freeHashTable(hashTable);
}

int main() {
    mainFunction();
    return 0;
}