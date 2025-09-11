
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1000
#define MAX_RECORDS 1000

struct KeyValue {
    char key[100];
    char value[100];
};

int compare(const void* a, const void* b) {
    return strcmp(((struct KeyValue*)a)->key, ((struct KeyValue*)b)->key);
}

struct KeyValue* sortKeyValueFile(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file\\n");
        return NULL;
    }

    struct KeyValue* records = malloc(MAX_RECORDS * sizeof(struct KeyValue));
    *count = 0;
    char line[MAX_LINE];
    
    while (fgets(line, MAX_LINE, file) && *count < MAX_RECORDS) {
        char* colon = strchr(line, ':');
        if (colon) {
            *colon = '\\0';
            // Trim key
            char* key = line;
            while (*key == ' ') key++;
            char* end = colon - 1;
            while (end > key && *end == ' ') end--;
            *(end + 1) = '\\0';
            
            // Trim value
            char* value = colon + 1;
            while (*value == ' ') value++;
            end = value + strlen(value) - 1;
            while (end > value && (*end == '\\n' || *end == ' ')) end--;
            *(end + 1) = '\\0';

            strcpy(records[*count].key, key);
            strcpy(records[*count].value, value);
            (*count)++;
        }
    }

    fclose(file);
    qsort(records, *count, sizeof(struct KeyValue), compare);
    return records;
}

int main() {
    // Create test file
    FILE* outFile = fopen("test.txt", "w");
    fprintf(outFile, "banana: yellow fruit\\n");
    fprintf(outFile, "apple: red fruit\\n");
    fprintf(outFile, "dog: pet animal\\n");
    fprintf(outFile, "cat: feline pet\\n");
    fprintf(outFile, "zebra: striped animal\\n");
    fclose(outFile);

    // Test cases
    int count;
    struct KeyValue* result = sortKeyValueFile("test.txt", &count);
    if (result) {
        for (int i = 0; i < count; i++) {
            printf("%s: %s\\n", result[i].key, result[i].value);
        }
        free(result);
    }

    return 0;
}
