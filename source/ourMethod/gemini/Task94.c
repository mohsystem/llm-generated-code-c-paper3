#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_VALUE_PAIRS 100
#define MAX_LINE_LENGTH 256


// Structure to store key-value pairs
typedef struct {
    char key[MAX_LINE_LENGTH];
    char value[MAX_LINE_LENGTH];
} KeyValuePair;

// Comparison function for qsort
int compareKeyValuePairs(const void *a, const void *b) {
    return strcmp(((KeyValuePair *)a)->key, ((KeyValuePair *)b)->key);
}


KeyValuePair* sortKeyValuePairsFromFile(const char *filePath, int *numPairs) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        *numPairs = 0;
        return NULL; 
    }

    KeyValuePair *keyValuePairs = (KeyValuePair *)malloc(MAX_KEY_VALUE_PAIRS * sizeof(KeyValuePair));
    *numPairs = 0;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file) != NULL && *numPairs < MAX_KEY_VALUE_PAIRS) {
        char *equalsPos = strchr(line, '=');
        if (equalsPos != NULL) {
            strncpy(keyValuePairs[*numPairs].key, line, equalsPos - line);
            keyValuePairs[*numPairs].key[equalsPos - line] = '\0';  // Null-terminate
            strcpy(keyValuePairs[*numPairs].value, equalsPos + 1);

            // Trim whitespace (newline, spaces, tabs) from key and value
            char *p = keyValuePairs[*numPairs].key;
            while (*p == ' ' || *p == '\t' || *p == '\n') p++;
            memmove(keyValuePairs[*numPairs].key, p, strlen(p) + 1); // Move including null terminator
            p = keyValuePairs[*numPairs].key + strlen(keyValuePairs[*numPairs].key) - 1;
            while (p >= keyValuePairs[*numPairs].key && (*p == ' ' || *p == '\t' || *p == '\n')) *p-- = '\0';

            p = keyValuePairs[*numPairs].value;
            while (*p == ' ' || *p == '\t' || *p == '\n') p++;
            memmove(keyValuePairs[*numPairs].value, p, strlen(p) + 1);
            p = keyValuePairs[*numPairs].value + strlen(keyValuePairs[*numPairs].value) - 1;
            while (p >= keyValuePairs[*numPairs].value && (*p == ' ' || *p == '\t' || *p == '\n')) *p-- = '\0';
            
            (*numPairs)++;
        }
    }
    fclose(file);


    qsort(keyValuePairs, *numPairs, sizeof(KeyValuePair), compareKeyValuePairs);
    return keyValuePairs;
}

int main() {
    // Test cases
    const char *testFiles[] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt"};
    int numTestFiles = sizeof(testFiles) / sizeof(testFiles[0]);

    for (int i = 0; i < numTestFiles; i++) {
        int numPairs;
        KeyValuePair *result = sortKeyValuePairsFromFile(testFiles[i], &numPairs);

        printf("\nTest %d:\n", i + 1);
        if (result != NULL ) {
            for (int j = 0; j < numPairs; j++) {
                printf("%s=%s\n", result[j].key, result[j].value);
            }
            free(result); // Free allocated memory
        } else {
           printf("Error reading or no data in file.\n"); // Indicate error
        }
    }

    return 0;
}