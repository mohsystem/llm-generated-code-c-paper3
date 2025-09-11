
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 10

typedef struct HashNode {
    char* key;
    int value;
    struct HashNode* next;
} HashNode;

typedef struct {
    HashNode** table;
    int size;
} Task152;

int hash(const char* key) {
    int hashCode = 0;
    while(*key) {
        hashCode = (hashCode * 31 + *key);
        key++;
    }
    return abs(hashCode % CAPACITY);
}

Task152* createHashTable() {
    Task152* ht = (Task152*)malloc(sizeof(Task152));
    if(!ht) return NULL;
    
    ht->table = (HashNode**)calloc(CAPACITY, sizeof(HashNode*));
    if(!ht->table) {
        free(ht);
        return NULL;
    }
    
    ht->size = 0;
    return ht;
}

void insert(Task152* ht, const char* key, int value) {
    if(!ht || !key) return;
    
    int index = hash(key);
    HashNode* node = ht->table[index];
    
    while(node != NULL) {
        if(strcmp(node->key, key) == 0) {
            node->value = value;
            return;
        }
        node = node->next;
    }
    
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    if(!newNode) return;
    
    newNode->key = strdup(key);
    if(!newNode->key) {
        free(newNode);
        return;
    }
    
    newNode->value = value;
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
    ht->size++;
}

int* search(Task152* ht, const char* key) {
    if(!ht || !key) return NULL;
    
    int index = hash(key);
    HashNode* node = ht->table[index];
    
    while(node != NULL) {
        if(strcmp(node->key, key) == 0) {
            int* result = (int*)malloc(sizeof(int));
            if(result) *result = node->value;
            return result;
        }
        node = node->next;
    }
    return NULL;
}

int delete(Task152* ht, const char* key) {
    if(!ht || !key) return 0;
    
    int index = hash(key);
    HashNode* node = ht->table[index];
    HashNode* prev = NULL;
    
    while(node != NULL) {
        if(strcmp(node->key, key) == 0) {
            if(prev == NULL) {
                ht->table[index] = node->next;
            } else {
                prev->next = node->next;
            }
            free(node->key);
            free(node);
            ht->size--;
            return 1;
        }
        prev = node;
        node = node->next;
    }
    return 0;
}

void freeHashTable(Task152* ht) {
    if(!ht) return;
    
    for(int i = 0; i < CAPACITY; i++) {
        HashNode* node = ht->table[i];
        while(node != NULL) {
            HashNode* temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

int main() {
    Task152* hashTable = createHashTable();
    
    // Test case 1: Insert and search
    insert(hashTable, "one", 1);
    int* result = search(hashTable, "one");
    printf("Test 1: %d\\n", (result != NULL && *result == 1));
    free(result);
    
    // Test case 2: Update existing key
    insert(hashTable, "one", 10);
    result = search(hashTable, "one");
    printf("Test 2: %d\\n", (result != NULL && *result == 10));
    free(result);
    
    // Test case 3: Delete existing key
    printf("Test 3: %d\\n", delete(hashTable, "one"));
    
    // Test case 4: Search non-existing key
    result = search(hashTable, "two");
    printf("Test 4: %d\\n", (result == NULL));
    
    // Test case 5: Delete non-existing key
    printf("Test 5: %d\\n", (!delete(hashTable, "two")));
    
    freeHashTable(hashTable);
    return 0;
}
