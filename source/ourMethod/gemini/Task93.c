#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a key-value pair
typedef struct {
    char *key;
    char *value;
} KeyValuePair;

// Comparison function for qsort (to sort by key)
int compareKeyValuePairs(const void *a, const void *b) {
    return strcmp(((KeyValuePair *)a)->key, ((KeyValuePair *)b)->key);
}


KeyValuePair* sortKeyValuePairs(const char *filePath, int *numPairs) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        *numPairs = 0; // Or handle error as needed
        return NULL;
    }

    KeyValuePair *keyValuePairs = NULL;
    *numPairs = 0;
    char line[256]; // Adjust as needed


    while (fgets(line, sizeof(line), file)) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        char *key = strtok(line, "=");
        char *value = strtok(NULL, ""); // Get the rest of the line as value

        if (key && value) {
            (*numPairs)++;
            keyValuePairs = realloc(keyValuePairs, (*numPairs) * sizeof(KeyValuePair));

            if (!keyValuePairs) {
               *numPairs = 0;
               fclose(file);
                return NULL; // Handle memory allocation error
            }
            // Allocate memory and copy strings, important for persistence
            keyValuePairs[*numPairs - 1].key = strdup(key);
            keyValuePairs[*numPairs - 1].value = strdup(value);
              if (!keyValuePairs[*numPairs - 1].key || !keyValuePairs[*numPairs - 1].value ) {
                 // Handle memory allocation error within the loop
                  fclose(file);
                  // Free already allocated memory
                  for(int i = 0; i < *numPairs; ++i) {
                      free(keyValuePairs[i].key);
                      free(keyValuePairs[i].value);
                   }
                  free(keyValuePairs);
                  *numPairs = 0;
                  return NULL; 
              }
        }
    }
    fclose(file);
    qsort(keyValuePairs, *numPairs, sizeof(KeyValuePair), compareKeyValuePairs);

    return keyValuePairs;
}

int main() {
    int numPairs;
     // Test cases
    KeyValuePair *result;
    int i;

    for (i = 1; i <= 5; i++) {
        char filename[20];
        sprintf(filename, "test%d.txt", i);
        result = sortKeyValuePairs(filename, &numPairs);

        printf("Test %d: ", i);
        if (result) {
            for (int j = 0; j < numPairs; j++) {
                printf("%s=%s ", result[j].key, result[j].value);
                free(result[j].key);  // Free allocated memory
                free(result[j].value);
            }
             free(result);
        }
        printf("\n");
    }
  

    return 0;
}