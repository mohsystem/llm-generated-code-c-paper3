#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* next;
} Node;

typedef struct HashTable {
    int bucket;
    Node** table;
} HashTable;

HashTable* createHashTable(int bucket) {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->bucket = bucket;
    hashTable->table = (Node**)calloc(bucket, sizeof(Node*));
    return hashTable;
}

int hashFunction(int key, int bucket) {
    return key % bucket;
}

void insertItem(HashTable* hashTable, int key) {
    int index = hashFunction(key, hashTable->bucket);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
}

void deleteItem(HashTable* hashTable, int key) {
    int index = hashFunction(key, hashTable->bucket);
    Node* prev = NULL;
    Node* current = hashTable->table[index];
    while (current != NULL && current->key != key) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) return;
    if (prev == NULL) {
        hashTable->table[index] = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
}

bool searchItem(HashTable* hashTable, int key) {
    int index = hashFunction(key, hashTable->bucket);
    Node* current = hashTable->table[index];
    while (current != NULL && current->key != key) {
        current = current->next;
    }
    return current != NULL;
}

void displayHash(HashTable* hashTable) {
    for (int i = 0; i < hashTable->bucket; i++) {
        printf("Index %d: ", i);
        Node* current = hashTable->table[i];
        while (current != NULL) {
            printf("%d ", current->key);
            current = current->next;
        }
        printf("\n");
    }
}

int main() {
    HashTable* hashTable = createHashTable(10);
    int keys[] = {15, 11, 27, 8, 12};
    int size = sizeof(keys) / sizeof(keys[0]);
    for (int i = 0; i < size; i++) {
        insertItem(hashTable, keys[i]);
    }
    displayHash(hashTable);
    printf("Searching for 11: %d\n", searchItem(hashTable, 11));
    printf("Searching for 27: %d\n", searchItem(hashTable, 27));
    deleteItem(hashTable, 11);
    displayHash(hashTable);
    printf("Searching for 11 after deletion: %d\n", searchItem(hashTable, 11));
    return 0;
}