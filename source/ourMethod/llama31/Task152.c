#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

typedef struct HashTable {
    int size;
    Node** table;
} HashTable;

HashTable* createHashTable(int size) {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->size = size;
    hashTable->table = (Node**)calloc(size, sizeof(Node*));
    return hashTable;
}

void freeHashTable(HashTable* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        Node* node = hashTable->table[i];
        while (node != NULL) {
            Node* next = node->next;
            free(node);
            node = next;
        }
    }
    free(hashTable->table);
    free(hashTable);
}

int hashFunction(int key, int size) {
    return key % size;
}

void insert(HashTable* hashTable, int key, int value) {
    int index = hashFunction(key, hashTable->size);
    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = (Node*)malloc(sizeof(Node));
        hashTable->table[index]->key = key;
        hashTable->table[index]->value = value;
        hashTable->table[index]->next = NULL;
    } else {
        Node* node = hashTable->table[index];
        while (node->next != NULL) {
            if (node->key == key) {
                node->value = value;
                return;
            }
            node = node->next;
        }
        if (node->key == key) {
            node->value = value;
        } else {
            node->next = (Node*)malloc(sizeof(Node));
            node->next->key = key;
            node->next->value = value;
            node->next->next = NULL;
        }
    }
}

void deleteKey(HashTable* hashTable, int key) {
    int index = hashFunction(key, hashTable->size);
    if (hashTable->table[index] == NULL) return;
    if (hashTable->table[index]->key == key) {
        Node* temp = hashTable->table[index];
        hashTable->table[index] = hashTable->table[index]->next;
        free(temp);
        return;
    }
    Node* node = hashTable->table[index];
    while (node->next != NULL) {
        if (node->next->key == key) {
            Node* temp = node->next;
            node->next = node->next->next;
            free(temp);
            return;
        }
        node = node->next;
    }
}

int search(HashTable* hashTable, int key) {
    int index = hashFunction(key, hashTable->size);
    if (hashTable->table[index] == NULL) return -1;
    Node* node = hashTable->table[index];
    while (node != NULL) {
        if (node->key == key) return node->value;
        node = node->next;
    }
    return -1;
}

void display(HashTable* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        printf("Index %d: ", i);
        Node* node = hashTable->table[i];
        while (node != NULL) {
            printf("%d -> %d ", node->key, node->value);
            node = node->next;
        }
        printf("\n");
    }
}

int main() {
    HashTable* hashTable = createHashTable(10);
    insert(hashTable, 1, 10);
    insert(hashTable, 2, 20);
    insert(hashTable, 11, 30); // Collision
    display(hashTable);
    printf("Search for key 1: %d\n", search(hashTable, 1));
    deleteKey(hashTable, 2);
    display(hashTable);
    freeHashTable(hashTable);
    return 0;
}