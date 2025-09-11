#include <stdio.h>
#include <stdlib.h>

typedef struct HashNode {
    int key;
    int value;
    struct HashNode* next;
} HashNode;

typedef struct Task152 {
    HashNode** buckets;
    int size;
    int numBuckets;
} Task152;

Task152* Task152_create() {
    Task152* hashTable = malloc(sizeof(Task152));
    hashTable->numBuckets = 10;
    hashTable->size = 0;
    hashTable->buckets = calloc(hashTable->numBuckets, sizeof(HashNode*));
    return hashTable;
}

void Task152_insert(Task152* hashTable, int key, int value) {
    int index = key % hashTable->numBuckets;
    HashNode* node = hashTable->buckets[index];
    while (node != NULL) {
        if (node->key == key) {
            node->value = value;
            return;
        }
        node = node->next;
    }
    node = malloc(sizeof(HashNode));
    node->key = key;
    node->value = value;
    node->next = hashTable->buckets[index];
    hashTable->buckets[index] = node;
    hashTable->size++;
    if ((float)hashTable->size / hashTable->numBuckets > 0.7) {
        Task152_resize(hashTable);
    }
}

int Task152_search(Task152* hashTable, int key) {
    int index = key % hashTable->numBuckets;
    HashNode* node = hashTable->buckets[index];
    while (node != NULL) {
        if (node->key == key) {
            return node->value;
        }
        node = node->next;
    }
    return -1; // Key not found
}

void Task152_delete(Task152* hashTable, int key) {
    int index = key % hashTable->numBuckets;
    HashNode* node = hashTable->buckets[index];
    HashNode* prev = NULL;
    while (node != NULL) {
        if (node->key == key) {
            if (prev == NULL) {
                hashTable->buckets[index] = node->next;
            } else {
                prev->next = node->next;
            }
            free(node);
            hashTable->size--;
            return;
        }
        prev = node;
        node = node->next;
    }
}

void Task152_resize(Task152* hashTable) {
    int newNumBuckets = hashTable->numBuckets * 2;
    HashNode** newBuckets = calloc(newNumBuckets, sizeof(HashNode*));
    for (int i = 0; i < hashTable->numBuckets; ++i) {
        HashNode* node = hashTable->buckets[i];
        while (node != NULL) {
            HashNode* nextNode = node->next;
            int newIndex = node->key % newNumBuckets;
            node->next = newBuckets[newIndex];
            newBuckets[newIndex] = node;
            node = nextNode;
        }
    }
    free(hashTable->buckets);
    hashTable->buckets = newBuckets;
    hashTable->numBuckets = newNumBuckets;
}

int main() {
    Task152* hashTable = Task152_create();
    Task152_insert(hashTable, 1, 10);
    Task152_insert(hashTable, 2, 20);
    Task152_insert(hashTable, 3, 30);
    printf("Search 1: %d\n", Task152_search(hashTable, 1)); // Output: 10
    printf("Search 2: %d\n", Task152_search(hashTable, 2)); // Output: 20
    Task152_delete(hashTable, 2);
    printf("Search 2 after delete: %d\n", Task152_search(hashTable, 2)); // Output: -1
    return 0;
}