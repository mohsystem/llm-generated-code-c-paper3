#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a key-value pair
typedef struct {
    char *key;
    char *value;
} KeyValuePair;

// Comparison function for sorting key-value pairs based on keys
int compareKeyValuePairs(const void *a, const void *b) {
    return strcmp(((KeyValuePair *)a)->key, ((KeyValuePair *)b)->key);
}

KeyValuePair* sortKeyValuePairs(const char *filePath, int *numPairs) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        *numPairs = 0;  // Set to zero to avoid potential issues.
        return NULL;
    }

    KeyValuePair *pairs = NULL;
    *numPairs = 0;
    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "\n"); // Remove newline from value

        if (key != NULL && value != NULL) {
            (*numPairs)++;
            pairs = realloc(pairs, (*numPairs) * sizeof(KeyValuePair));
            if (pairs == NULL) {
                fclose(file);
                return NULL; // Memory allocation failed
            }

            pairs[*numPairs - 1].key = strdup(key);
            pairs[*numPairs - 1].value = strdup(value);

             //Remove leading/trailing whitespace from key & value
             char *start = pairs[*numPairs - 1].key;
             while(*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r') {
                start++;
             }
             char *end = start + strlen(start) -1 ;
             while(*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r') {
                 *end = '\0';
                 end--;
             }
             pairs[*numPairs - 1].key = strdup(start);

             start = pairs[*numPairs - 1].value;
             while(*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r') {
                 start++;
             }

             end = start + strlen(start) -1 ;
             while(*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r') {
                 *end = '\0';
                 end--;
             }

             pairs[*numPairs - 1].value = strdup(start);
        }
    }

    fclose(file);
    qsort(pairs, *numPairs, sizeof(KeyValuePair), compareKeyValuePairs);
    return pairs;
}


int main() {
    char *testFiles[] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt"};
    int numTestFiles = sizeof(testFiles) / sizeof(testFiles[0]);

    for (int i = 0; i < numTestFiles; i++) {
        int numPairs;
        KeyValuePair *sortedPairs = sortKeyValuePairs(testFiles[i], &numPairs);

        if (sortedPairs != NULL) {
            for (int j = 0; j < numPairs; j++) {
                printf("%s=%s\n", sortedPairs[j].key, sortedPairs[j].value);
                free(sortedPairs[j].key);
                free(sortedPairs[j].value);
            }
            free(sortedPairs);
        } else {
             printf("File not found or error occurred.\n");
        }
         printf("\n");
    }

    return 0;
}