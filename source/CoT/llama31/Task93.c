#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold key-value pairs
typedef struct {
    char key[100];
    char value[100];
} KeyValue;

// Function to compare two key-value pairs for sorting
int compare(const void* a, const void* b) {
    KeyValue* kv1 = (KeyValue*)a;
    KeyValue* kv2 = (KeyValue*)b;
    return strcmp(kv1->key, kv2->key);
}

void sortKeyValueRecords(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        fprintf(stderr, "Error reading file: %s\n", fileName);
        return;
    }

    KeyValue keyValuePairs[100];
    int count = 0;

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char* equalsPos = strchr(line, '=');
        if (equalsPos != NULL) {
            *equalsPos = '\0'; // Split the line at the '='
            strcpy(keyValuePairs[count].key, line);
            strcpy(keyValuePairs[count].value, equalsPos + 1);
            count++;
        } else {
            printf("Skipping invalid line: %s", line);
        }
    }
    fclose(file);

    // Sort the key-value pairs
    qsort(keyValuePairs, count, sizeof(KeyValue), compare);

    // Write the sorted key-value pairs to a new file
    FILE* outputFile = fopen("sorted_" + fileName, "w");
    if (!outputFile) {
        fprintf(stderr, "Error writing file: %s\n", fileName);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(outputFile, "%s=%s\n", keyValuePairs[i].key, keyValuePairs[i].value);
    }
    fclose(outputFile);
}

int main() {
    const char* testFiles[] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt"};
    for (const char* file : testFiles) {
        sortKeyValueRecords(file);
    }
    return 0;
}