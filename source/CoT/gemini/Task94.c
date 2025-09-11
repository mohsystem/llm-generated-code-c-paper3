#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a key-value pair
typedef struct {
    char key[100];
    char value[100];
} KeyValuePair;

// Comparison function for sorting
int compareKeyValuePairs(const void *a, const void *b) {
    return strcmp(((KeyValuePair *)a)->key, ((KeyValuePair *)b)->key);
}


KeyValuePair* sortKeyValuePairs(const char *filePath, int *numPairs) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        *numPairs = 0;
        return NULL; 
    }

    KeyValuePair *pairs = NULL;
    *numPairs = 0;
    char line[256];


    while (fgets(line, sizeof(line), file) != NULL) {
        char *key = strtok(line, ",");
        char *value = strtok(NULL, "\n"); // Get value up to newline

         if (key != NULL && value != NULL) {
            (*numPairs)++;
            pairs = realloc(pairs, (*numPairs) * sizeof(KeyValuePair));
            if (pairs == NULL) {
                perror("Memory allocation failed");
                fclose(file);
                return NULL;
            }

            // Remove leading/trailing whitespace from key and value
            char *start = key;
            while (*start == ' ' || *start == '\t' ) {
                start++;
            }
            char *end = key + strlen(key) - 1;
            while (end > start && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
                *end-- = '\0';
            }
            strcpy(pairs[(*numPairs) - 1].key, start);


            start = value;
            while (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r') {
                start++;
            }
            end = value + strlen(value) - 1;
            while (end > start && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
                *end-- = '\0';
            }
            strcpy(pairs[(*numPairs) - 1].value, start);

        }
    }

    fclose(file);
    qsort(pairs, *numPairs, sizeof(KeyValuePair), compareKeyValuePairs);
    return pairs;
}


int main() {
    int numPairs;

     KeyValuePair *result1 = sortKeyValuePairs("test1.txt", &numPairs);
    printf("Test 1:\n");
    for (int i = 0; i < numPairs; i++) {
        printf("%s: %s\n", result1[i].key, result1[i].value);
    }
    free(result1);

     KeyValuePair *result2 = sortKeyValuePairs("test2.txt", &numPairs);
    printf("\nTest 2:\n");
    for (int i = 0; i < numPairs; i++) {
        printf("%s: %s\n", result2[i].key, result2[i].value);
    }
    free(result2);

      KeyValuePair *result3 = sortKeyValuePairs("test3.txt", &numPairs);
    printf("\nTest 3:\n");
    for (int i = 0; i < numPairs; i++) {
        printf("%s: %s\n", result3[i].key, result3[i].value);
    }
    free(result3);

      KeyValuePair *result4 = sortKeyValuePairs("test4.txt", &numPairs);
    printf("\nTest 4:\n");
    for (int i = 0; i < numPairs; i++) {
        printf("%s: %s\n", result4[i].key, result4[i].value);
    }
    free(result4);

      KeyValuePair *result5 = sortKeyValuePairs("test5.txt", &numPairs);
    printf("\nTest 5:\n");
    for (int i = 0; i < numPairs; i++) {
        printf("%s: %s\n", result5[i].key, result5[i].value);
    }
    free(result5);


    return 0;
}