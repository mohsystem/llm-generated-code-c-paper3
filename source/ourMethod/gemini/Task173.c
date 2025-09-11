#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Implement a hash table for C (limited functionality for this problem)
typedef struct {
    char *key;
    int value;
} HashEntry;

typedef struct {
    HashEntry *entries;
    int size;
    int count;
} HashTable;


HashTable *createHashTable(int size) {
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    ht->entries = (HashEntry *)calloc(size, sizeof(HashEntry));
    ht->size = size;
    ht->count = 0;
    return ht;
}


void freeHashTable(HashTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        if (ht->entries[i].key != NULL) {
            free(ht->entries[i].key);
        }
    }
    free(ht->entries);
    free(ht);
}


int hash(const char *str) {
    int hash = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        hash = (hash * 31 + str[i]) ; // Simple hash function
    }
    return abs(hash);
}


int insert(HashTable *ht, const char *key) {
    int index = hash(key) % ht->size;

        if (ht->entries[index].key == NULL || strcmp(ht->entries[index].key, key) == 0 ) {
           if(ht->entries[index].key == NULL) {
               ht->entries[index].key = strdup(key); // Important: Allocate memory and copy
               ht->entries[index].value = 1;
               ht->count++;
           } else {
                ht->entries[index].value++;
           }
           if(ht->entries[index].value == 2)
                return 1; // Found duplicate
        }

    return 0;
}


char *longestDupSubstring(const char *s) {
    int n = strlen(s);
    int left = 1;
    int right = n - 1;
    char *result = "";

    while (left <= right) {
        int mid = left + (right - left) / 2;
        char *dup = findDuplicateSubstring(s, mid);

        if (dup != NULL && strlen(dup) > strlen(result) ) {
                if(result != "")
                    free(result); // Prevent memory leaks

                result = dup;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

char *findDuplicateSubstring(const char *s, int len) {
    int n = strlen(s);
    HashTable *seen = createHashTable(n * 2); // Size should be larger than n to reduce collisions
    for (int i = 0; i <= n - len; i++) {
        char *sub = (char*) malloc(len + 1);
        strncpy(sub, s + i, len);
        sub[len] = '\0'; // Null terminate

        if (insert(seen, sub)) {
                freeHashTable(seen);
            return sub;
        }
    }

    freeHashTable(seen);
    return NULL;
}

int main() {
    char *testCases[] = {"banana", "abcd", "abracadabra", "aabaab", "aaaaaaaa"};
    char *expectedOutputs[] = {"ana", "", "abra", "aab", "aaaaaaa"};

    for (int i = 0; i < 5; i++) {
        char *output = longestDupSubstring(testCases[i]);
        printf("Test case %d: Input - %s, Output - %s, Expected - %s\n", i + 1, testCases[i], output, expectedOutputs[i]);
         assert(strcmp(output, expectedOutputs[i]) == 0);
        if(strcmp(output, "") != 0) {
            free(output);
        }

    }

    printf("All test cases passed.\n");
    return 0;
}