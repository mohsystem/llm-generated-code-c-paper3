#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a key-value pair
typedef struct {
    char key[100];
    char value[100];
} KeyValuePair;

// Comparison function for qsort
int compareKeyValuePairs(const void *a, const void *b) {
    return strcmp(((KeyValuePair *)a)->key, ((KeyValuePair *)b)->key);
}

KeyValuePair* sortKeyValueFile(const char *filePath, int *numPairs) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    KeyValuePair *keyValuePairs = NULL;
    *numPairs = 0;
    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "=");

        if (key != NULL && value != NULL) {
            (*numPairs)++;
            keyValuePairs = realloc(keyValuePairs, (*numPairs) * sizeof(KeyValuePair));
            if (keyValuePairs == NULL) {
                perror("Memory allocation error");
                fclose(file);
                return NULL;
            }
             //Trim whitespace
            char *start = key;
            while (*start == ' ' || *start == '\t' || *start == '\n') {
                start++;
            }
            char *end = key + strlen(key) - 1;
            while (*end == ' ' || *end == '\t' || *end == '\n') {
                end--;
            }
            *(end + 1) = '\0';
            strcpy(keyValuePairs[*numPairs - 1].key, start);

             start = value;
            while (*start == ' ' || *start == '\t' || *start == '\n') {
                start++;
            }
            end = value + strlen(value) - 1;
            while (*end == ' ' || *end == '\t' || *end == '\n') {
                end--;
            }
            *(end + 1) = '\0';
            strcpy(keyValuePairs[*numPairs - 1].value, start);



        }
    }

    fclose(file);

    qsort(keyValuePairs, *numPairs, sizeof(KeyValuePair), compareKeyValuePairs);
    return keyValuePairs;
}

int main() {
    // Test cases (similar structure as other languages)
     char *test_cases[][2] = {
        {"key1", "value1"}, {"key3", "value3"}, {"key2", "value2"}, {"key4", "value4"}, {"key5", "value5"},
        {"apple", "red"}, {"banana", "yellow"}, {"orange", "orange"}, {"grape", "purple"}, {"kiwi", "green"},
        {"one", "1"}, {"two", "2"}, {"three", "3"}, {"four", "4"}, {"five", "5"},
        {"red", "apple"}, {"yellow", "banana"}, {"orange", "orange"}, {"purple", "grape"}, {"green", "kiwi"},
        {"1", "one"}, {"2", "two"}, {"3", "three"}, {"4", "four"}, {"5", "five"}
    };


    for (int i = 0; i < 5; i++) {
        char filename[20];
        sprintf(filename, "test_%d.txt", i + 1);

        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error creating test file");
            continue; // Skip to next test case
        }

        for (int j = 0; j < 5; j++) {
            fprintf(file, "%s=%s\n", test_cases[i*5 +j][0], test_cases[i*5 + j][1]);
        }
        fclose(file);

        int numPairs;
        KeyValuePair *sortedPairs = sortKeyValueFile(filename, &numPairs);

        if (sortedPairs != NULL) {
            for (int j = 0; j < numPairs; j++) {
                printf("%s=%s\n", sortedPairs[j].key, sortedPairs[j].value);
            }
             printf("---\n");
            free(sortedPairs); // Free allocated memory
        }
    }


    return 0;
}