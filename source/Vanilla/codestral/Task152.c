#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char* key;
    int value;
} HashNode;

HashNode* hashTable[MAX_SIZE] = {NULL};

unsigned int hash(char* str) {
    unsigned int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash % MAX_SIZE;
}

void insert(char* key, int value) {
    unsigned int index = hash(key);
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    node->key = strdup(key);
    node->value = value;
    hashTable[index] = node;
}

void deleteKey(char* key) {
    unsigned int index = hash(key);
    HashNode* node = hashTable[index];

    if (node == NULL)
        return;

    free(node->key);
    free(node);
    hashTable[index] = NULL;
}

int search(char* key) {
    unsigned int index = hash(key);
    HashNode* node = hashTable[index];

    if (node == NULL)
        return -1;  // or throw an exception, depending on your needs

    return node->value;
}

int main() {
    insert("one", 1);
    insert("two", 2);
    insert("three", 3);

    printf("%d\n", search("two"));  // 2

    deleteKey("two");

    printf("%d\n", search("two"));  // -1

    return 0;
}