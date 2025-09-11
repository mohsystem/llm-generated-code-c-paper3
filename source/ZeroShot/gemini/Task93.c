#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a key-value pair
typedef struct {
    char key[100];
    char value[100];
} KeyValuePair;

// Comparison function for sorting key-value pairs based on keys
int comparePairs(const void *a, const void *b) {
    return strcmp(((KeyValuePair *)a)->key, ((KeyValuePair *)b)->key);
}

KeyValuePair* sortKeyValuePairs(const char *filePath, int *numPairs) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        *numPairs = 0;  // Indicate file open failure
        return NULL;
    }

    KeyValuePair *pairs = NULL;
    *numPairs = 0;
    char line[200];

    while (fgets(line, sizeof(line), file) != NULL) {
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "=");

        if (key != NULL && value != NULL) {
            (*numPairs)++;
            pairs = realloc(pairs, (*numPairs) * sizeof(KeyValuePair));
            if (pairs == NULL) {
                // Handle memory allocation error
                fclose(file);
                *numPairs = 0;
                return NULL;
            }
            
            // Remove leading/trailing whitespace from key and value
            char *start = key;
            while (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r') {
                start++;
            }
            char *end = key + strlen(key) - 1;
            while (end >= key && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
                end--;
            }
            *(end + 1) = '\0';

            start = value;
            while (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r') {
                start++;
            }
            end = value + strlen(value) - 1;
             while (end >= value && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
                end--;
            }
            *(end + 1) = '\0';

            strcpy(pairs[(*numPairs) - 1].key, key);
            strcpy(pairs[(*numPairs) - 1].value, value);
        }
    }

    fclose(file);

    // Sort the pairs based on keys
    qsort(pairs, *numPairs, sizeof(KeyValuePair), comparePairs);

    return pairs;
}

int main() {
    char *testFiles[] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt"};
    int numTestFiles = sizeof(testFiles) / sizeof(testFiles[0]);

    for (int i = 0; i < numTestFiles; i++) {
        printf("\nTest case %d:\n", i + 1);
        int numPairs;
        KeyValuePair *sortedPairs = sortKeyValuePairs(testFiles[i], &numPairs);

        if (sortedPairs != NULL && numPairs > 0) {
           for (int j = 0; j < numPairs; j++) {
                printf("%s=%s\n", sortedPairs[j].key, sortedPairs[j].value);
            }
            free(sortedPairs);
        } else {
            fprintf(stderr, "Error opening or processing file: %s\n", testFiles[i]);
        }
    }

    return 0;
}