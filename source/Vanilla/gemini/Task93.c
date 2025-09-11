#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to hold key-value pairs
typedef struct {
    char key[100];
    char value[100];
} KeyValuePair;

// Comparison function for sorting key-value pairs
int compareKeyValuePairs(const void *a, const void *b) {
    return strcmp(((KeyValuePair *)a)->key, ((KeyValuePair *)b)->key);
}


KeyValuePair* sortKeyValueFile(const char *filePath, int *numPairs) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        *numPairs = 0;
        return NULL;
    }

    KeyValuePair *keyValuePairs = NULL;
    *numPairs = 0;
    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        char key[100], value[100];
        if (sscanf(line, "%s=%s", key, value) == 2) {
            (*numPairs)++;
            keyValuePairs = realloc(keyValuePairs, (*numPairs) * sizeof(KeyValuePair));
            strcpy(keyValuePairs[(*numPairs) - 1].key, key);

            strcpy(keyValuePairs[(*numPairs) - 1].value, value);

        }
    }

    fclose(file);


    qsort(keyValuePairs, *numPairs, sizeof(KeyValuePair), compareKeyValuePairs);

    return keyValuePairs;
}

int main() {
    int numPairs;
    for(int i = 1; i <= 5; ++i) {
        char filename[20];
        sprintf(filename, "file%d.txt", i); // create filenames like file1.txt, file2.txt...

        KeyValuePair *pairs = sortKeyValueFile(filename, &numPairs);

        if (pairs != NULL) {
            for (int j = 0; j < numPairs; j++) {
                printf("%s=%s\n", pairs[j].key, pairs[j].value);
            }
            free(pairs);
            printf("\n"); // Add a newline for separation between file outputs
        }
    }

    return 0;
}