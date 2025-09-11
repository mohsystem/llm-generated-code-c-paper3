#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a simple hash table implementation
// Note: This is a basic example and lacks robust error handling and features.

#define TABLE_SIZE 10

typedef struct {
    char *key;
    char *value;
} Entry;

typedef struct {
    Entry *entries[TABLE_SIZE];
} HashTable;


unsigned int hash(const char *key) {
    unsigned int hashValue = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hashValue += key[i];
        hashValue *= 31; // A common prime number for hashing
    }
    return hashValue % TABLE_SIZE;
}

void insert(HashTable *table, const char *key, const char *value) {
    unsigned int index = hash(key);
    
    if (table->entries[index] == NULL) {
        table->entries[index] = (Entry*)malloc(sizeof(Entry));
        table->entries[index]->key = strdup(key);
        table->entries[index]->value = strdup(value);

    } else if (strcmp(table->entries[index]->key, key) == 0) {
        free(table->entries[index]->value); // Free the old value
        table->entries[index]->value = strdup(value); //Update value
    } else {
      //Handle collision (e.g. separate chaining or other methods), in real code.
      fprintf(stderr, "Collision at index %u. Key '%s' not inserted\n", index, key);

    }

}


char* search(HashTable *table, const char *key) {
    unsigned int index = hash(key);

    if (table->entries[index] != NULL && strcmp(table->entries[index]->key, key) == 0) {
        return table->entries[index]->value;
    }
    return NULL;
}

void delete_entry(HashTable *table, const char *key) {
    unsigned int index = hash(key);
    if (table->entries[index] != NULL && strcmp(table->entries[index]->key, key) == 0) {
        free(table->entries[index]->key);
        free(table->entries[index]->value);
        free(table->entries[index]);
        table->entries[index] = NULL;
    }
}


int main() {
    HashTable hashTable;
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable.entries[i] = NULL;
    }

    insert(&hashTable, "apple", "red");
    insert(&hashTable, "banana", "yellow");
    insert(&hashTable, "grape", "purple");

    printf("%s\n", search(&hashTable, "banana")); // Output: yellow
    delete_entry(&hashTable, "banana"); 
    printf("%s\n", search(&hashTable, "banana")); // Output: (null)

    insert(&hashTable, "apple", "green");
    printf("%s\n", search(&hashTable, "apple")); // Output: green


    HashTable ht;
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht.entries[i] = NULL;
    }
    insert(&ht, "one", "1");
    insert(&ht, "two", "2");
    insert(&ht, "three", "3");
    insert(&ht, "four", "4");
    insert(&ht, "five", "5");

    printf("%s\n", search(&ht, "two"));
    delete_entry(&ht, "two");
    printf("%s\n", search(&ht, "two")); // Output: (null)



    // Clean up memory (important!)

    for (int i = 0; i < TABLE_SIZE; i++) {
      if(hashTable.entries[i] != NULL){
        free(hashTable.entries[i]->key);
        free(hashTable.entries[i]->value);
        free(hashTable.entries[i]);
      }

      if(ht.entries[i] != NULL) {
        free(ht.entries[i]->key);
        free(ht.entries[i]->value);
        free(ht.entries[i]);

      }

    }




    return 0;
}