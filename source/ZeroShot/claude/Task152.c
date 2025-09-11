
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LENGTH 100

typedef struct HashNode {
    char key[MAX_KEY_LENGTH];
    int value;
    struct HashNode* next;
} HashNode;

typedef struct {
    HashNode** buckets;
    int size;
    int capacity;
} HashTable;

int hash_function(const char* key, int capacity) {
    int hash = 0;
    while(*key) {
        hash = (hash * 31 + *key) % capacity;
        key++;
    }
    return abs(hash % capacity);
}

HashTable* create_hash_table(int capacity) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->capacity = capacity;
    ht->size = 0;
    ht->buckets = (HashNode**)calloc(capacity, sizeof(HashNode*));
    return ht;
}

void insert(HashTable* ht, const char* key, int value) {
    int index = hash_function(key, ht->capacity);
    HashNode* node = ht->buckets[index];
    
    while(node != NULL) {
        if(strcmp(node->key, key) == 0) {
            node->value = value;
            return;
        }
        node = node->next;
    }
    
    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    strncpy(new_node->key, key, MAX_KEY_LENGTH - 1);
    new_node->key[MAX_KEY_LENGTH - 1] = '\\0';
    new_node->value = value;
    new_node->next = ht->buckets[index];
    ht->buckets[index] = new_node;
    ht->size++;
}

int delete(HashTable* ht, const char* key) {
    int index = hash_function(key, ht->capacity);
    HashNode* node = ht->buckets[index];
    HashNode* prev = NULL;
    
    while(node != NULL) {
        if(strcmp(node->key, key) == 0) {
            if(prev == NULL) {
                ht->buckets[index] = node->next;
            } else {
                prev->next = node->next;
            }
            free(node);
            ht->size--;
            return 1;
        }
        prev = node;
        node = node->next;
    }
    return 0;
}

int search(HashTable* ht, const char* key, int* value) {
    int index = hash_function(key, ht->capacity);
    HashNode* node = ht->buckets[index];
    
    while(node != NULL) {
        if(strcmp(node->key, key) == 0) {
            *value = node->value;
            return 1;
        }
        node = node->next;
    }
    return 0;
}

void free_hash_table(HashTable* ht) {
    for(int i = 0; i < ht->capacity; i++) {
        HashNode* node = ht->buckets[i];
        while(node != NULL) {
            HashNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(ht->buckets);
    free(ht);
}

int main() {
    HashTable* ht = create_hash_table(10);
    int value;
    
    // Test case 1: Insert and search
    insert(ht, "apple", 5);
    printf("Search apple: %s\\n", search(ht, "apple", &value) ? "found" : "not found");
    if(search(ht, "apple", &value)) printf("Value: %d\\n", value);
    
    // Test case 2: Update existing key
    insert(ht, "apple", 10);
    printf("Search apple after update: %s\\n", search(ht, "apple", &value) ? "found" : "not found");
    if(search(ht, "apple", &value)) printf("Value: %d\\n", value);
    
    // Test case 3: Search non-existent key
    printf("Search banana: %s\\n", search(ht, "banana", &value) ? "found" : "not found");
    
    // Test case 4: Delete existing key
    printf("Delete apple: %s\\n", delete(ht, "apple") ? "true" : "false");
    
    // Test case 5: Delete non-existent key
    printf("Delete banana: %s\\n", delete(ht, "banana") ? "true" : "false");
    
    free_hash_table(ht);
    return 0;
}
