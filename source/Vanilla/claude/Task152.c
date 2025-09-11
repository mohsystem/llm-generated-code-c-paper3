
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 769

struct HashNode {
    char key[50];
    int value;
    struct HashNode* next;
};

struct Task152 {
    struct HashNode* table[SIZE];
};

int hash(char* key) {
    int hash = 0;
    for(int i = 0; key[i] != '\\0'; i++) {
        hash = (hash * 31 + key[i]) % SIZE;
    }
    return hash;
}

struct HashNode* createNode(char* key, int value) {
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void insert(struct Task152* hashTable, char* key, int value) {
    int index = hash(key);
    struct HashNode* node = hashTable->table[index];
    
    while(node != NULL) {
        if(strcmp(node->key, key) == 0) {
            node->value = value;
            return;
        }
        node = node->next;
    }
    
    struct HashNode* newNode = createNode(key, value);
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
}

int search(struct Task152* hashTable, char* key) {
    int index = hash(key);
    struct HashNode* node = hashTable->table[index];
    
    while(node != NULL) {
        if(strcmp(node->key, key) == 0) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}

void delete_key(struct Task152* hashTable, char* key) {
    int index = hash(key);
    struct HashNode* node = hashTable->table[index];
    struct HashNode* prev = NULL;
    
    while(node != NULL && strcmp(node->key, key) != 0) {
        prev = node;
        node = node->next;
    }
    
    if(node == NULL) return;
    
    if(prev == NULL) {
        hashTable->table[index] = node->next;
    } else {
        prev->next = node->next;
    }
    free(node);
}

int main() {
    struct Task152 hashTable;
    for(int i = 0; i < SIZE; i++) {
        hashTable.table[i] = NULL;
    }
    
    // Test case 1: Insert and search
    insert(&hashTable, "apple", 5);
    printf("%d\\n", search(&hashTable, "apple"));  // 1
    
    // Test case 2: Insert duplicate
    insert(&hashTable, "apple", 10);
    insert(&hashTable, "banana", 7);
    printf("%d\\n", search(&hashTable, "banana"));  // 1
    
    // Test case 3: Delete and search
    delete_key(&hashTable, "apple");
    printf("%d\\n", search(&hashTable, "apple"));  // 0
    
    // Test case 4: Search non-existent
    printf("%d\\n", search(&hashTable, "orange"));  // 0
    
    // Test case 5: Multiple operations
    insert(&hashTable, "grape", 3);
    insert(&hashTable, "mango", 8);
    delete_key(&hashTable, "banana");
    printf("%d\\n", search(&hashTable, "grape"));  // 1
    printf("%d\\n", search(&hashTable, "banana"));  // 0
    
    return 0;
}
