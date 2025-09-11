#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Entry {
    char *key;
    char *value;
    struct Entry *next;
} Entry;

Entry *table[TABLE_SIZE];

unsigned int hash(const char *key) {
    unsigned int hashVal = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hashVal = hashVal * 31 + key[i]; // Simple hash function
    }
    return hashVal % TABLE_SIZE;
}

void insert(const char *key, const char *value) {
    unsigned int index = hash(key);
    Entry *newEntry = (Entry *)malloc(sizeof(Entry));
    if (newEntry == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    newEntry->key = strdup(key);  // Duplicate the key string
    newEntry->value = strdup(value); // Duplicate the value string
    newEntry->next = table[index];
    table[index] = newEntry;
}

void deleteKey(const char *key) {
    unsigned int index = hash(key);
    Entry *prev = NULL;
    Entry *current = table[index];

    while (current != NULL && strcmp(current->key, key) != 0) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (prev == NULL) {
            table[index] = current->next;
        } else {
            prev->next = current->next;
        }
        free(current->key);  // Free duplicated key string
        free(current->value); // Free duplicated value string
        free(current);
    }
}


char *search(const char *key) {
    unsigned int index = hash(key);
    Entry *current = table[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

int main() {
    // Test cases
    insert("apple", "red");
    insert("banana", "yellow");
    insert("grape", "purple");
    insert("orange", "orange");
    insert("kiwi", "green");


    printf("Search for apple: %s\n", search("apple"));
    printf("Search for grape: %s\n", search("grape"));
    printf("Search for nonexistent: %s\n", search("nonexistent"));

    deleteKey("banana");
    printf("Search for banana after deletion: %s\n", search("banana"));

    insert("apple", "green"); // Update value
    printf("Search for apple after update: %s\n", search("apple"));


    return 0;
}