#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold key-value records
typedef struct Record {
    char* key;
    char* value;
} Record;

// Function to compare two records for sorting
int compareRecords(const void* a, const void* b) {
    Record* r1 = (Record*)a;
    Record* r2 = (Record*)b;
    return strcmp(r1->key, r2->key);
}

void sortKeyValueRecords(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    int count = 0;
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        count++;
    }
    rewind(file);

    Record* records = (Record*)malloc(count * sizeof(Record));
    for (int i = 0; i < count; i++) {
        fgets(line, sizeof(line), file);
        line[strcspn(line, "\n")] = 0; // Remove newline character
        records[i].key = strdup(line);
    }
    fclose(file);

    qsort(records, count, sizeof(Record), compareRecords);

    file = fopen(fileName, "w");
    if (!file) {
        printf("Error opening file for writing\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\n", records[i].key);
    }
    fclose(file);

    // Print the sorted records
    for (int i = 0; i < count; i++) {
        printf("%s\n", records[i].key);
        free(records[i].key);
    }
    free(records);
}

int main() {
    const char* testFiles[] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt"};
    for (int i = 0; i < 5; i++) {
        sortKeyValueRecords(testFiles[i]);
    }
    return 0;
}