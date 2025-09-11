
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_PAIRS 1000

typedef struct {
    char* key;
    char* value;
} KeyValue;

int compare(const void* a, const void* b) {
    return strcmp(((KeyValue*)a)->key, ((KeyValue*)b)->key);
}

void readAndSortKeyValueFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\\n", filename);
        return;
    }

    KeyValue* pairs = malloc(MAX_PAIRS * sizeof(KeyValue));
    if (pairs == NULL) {
        fprintf(stderr, "Memory allocation failed\\n");
        fclose(file);
        return;
    }

    char line[MAX_LINE];
    int count = 0;

    while (fgets(line, sizeof(line), file) && count < MAX_PAIRS) {
        char* equals = strchr(line, '=');
        if (equals != NULL) {
            *equals = '\\0';
            char* key = line;
            char* value = equals + 1;

            // Remove newline if present
            char* newline = strchr(value, '\\n');
            if (newline) *newline = '\\0';

            // Trim spaces from key
            while (*key == ' ' || *key == '\\t') key++;
            char* end = key + strlen(key) - 1;
            while (end > key && (*end == ' ' || *end == '\\t')) end--;
            *(end + 1) = '\\0';

            // Trim spaces from value
            while (*value == ' ' || *value == '\\t') value++;
            end = value + strlen(value) - 1;
            while (end > value && (*end == ' ' || *end == '\\t')) end--;
            *(end + 1) = '\\0';

            if (strlen(key) > 0) {
                pairs[count].key = strdup(key);
                pairs[count].value = strdup(value);
                if (pairs[count].key == NULL || pairs[count].value == NULL) {
                    fprintf(stderr, "Memory allocation failed\\n");
                    break;
                }
                count++;
            }
        }
    }

    fclose(file);

    // Sort the pairs
    qsort(pairs, count, sizeof(KeyValue), compare);

    // Print sorted pairs
    for (int i = 0; i < count; i++) {
        printf("%s=%s\\n", pairs[i].key, pairs[i].value);
        free(pairs[i].key);
        free(pairs[i].value);
    }

    free(pairs);
}

int main() {
    // Test cases
    FILE* testFile = fopen("test.txt", "w");
    if (testFile != NULL) {
        fprintf(testFile, "b=value2\\n");
        fprintf(testFile, "a=value1\\n");
        fprintf(testFile, "d=value4\\n");
        fprintf(testFile, "c=value3\\n");
        fprintf(testFile, "e=value5\\n");
        fclose(testFile);
        
        readAndSortKeyValueFile("test.txt");
    } else {
        fprintf(stderr, "Error creating test file\\n");
    }

    return 0;
}
