
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR 0.75

typedef struct HashNode {
    char* key;
    int value;
    struct HashNode* next;
} HashNode;

typedef struct {
    HashNode** buckets;
    int capacity;
    int size;
} Task152;

unsigned int hash_function(const char* key, int capacity) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key;
        key++;
    }
    return hash % capacity;
}

Task152* create_hash_table() {
    Task152* table = (Task152*)malloc(sizeof(Task152));
    if (!table) return NULL;

    table->capacity = INITIAL_CAPACITY;
    table->size = 0;
    table->buckets = (HashNode**)calloc(INITIAL_CAPACITY, sizeof(HashNode*));
    
    if (!table->buckets) {
        free(table);
        return NULL;
    }
    
    return table;
}

void resize_hash_table(Task152* table) {
    if (!table) return;

    HashNode** old_buckets = table->buckets;
    int old_capacity = table->capacity;
    
    table->capacity *= 2;
    table->buckets = (HashNode**)calloc(table->capacity, sizeof(HashNode*));
    if (!table->buckets) {
        table->buckets = old_buckets;
        table->capacity = old_capacity;
        return;
    }
    
    table->size = 0;
    
    for (int i = 0; i < old_capacity; i++) {
        HashNode* current = old_buckets[i];
        while (current != NULL) {
            HashNode* temp = current->next;
            unsigned int index = hash_function(current->key, table->capacity);
            
            current->next = table->buckets[index];
            table->buckets[index] = current;
            table->size++;
            
            current = temp;
        }
    }
    
    free(old_buckets);
}

void insert(Task152* table, const char* key, int value) {
    if (!table || !key) return;

    if ((double)table->size / table->capacity >= LOAD_FACTOR) {
        resize_hash_table(table);
    }

    unsigned int index = hash_function(key, table->capacity);
    HashNode* current = table->buckets[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return;
        }
        current = current->next;
    }

    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    if (!new_node) return;

    new_node->key = strdup(key);
    if (!new_node->key) {
        free(new_node);
        return;
    }

    new_node->value = value;
    new_node->', type='text')