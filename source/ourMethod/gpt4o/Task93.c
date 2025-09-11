#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

typedef struct Record {
    char key[MAX_LINE_LENGTH];
    char value[MAX_LINE_LENGTH];
} Record;

int compareRecords(const void *a, const void *b) {
    Record *recordA = (Record *)a;
    Record *recordB = (Record *)b;
    return strcmp(recordA->key, recordB->key);
}

Record* readAndSortKeyValueFile(const char *filePath, int *recordCount) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", filePath);
        *recordCount = 0;
        return NULL;
    }

    Record *records = NULL;
    char line[MAX_LINE_LENGTH];
    *recordCount = 0;

    while (fgets(line, sizeof(line), file)) {
        char *pos = strchr(line, '=');
        if (pos) {
            *pos = '\0';
            records = realloc(records, (*recordCount + 1) * sizeof(Record));
            strncpy(records[*recordCount].key, line, MAX_LINE_LENGTH);
            strncpy(records[*recordCount].value, pos + 1, MAX_LINE_LENGTH);
            (*recordCount)++;
        }
    }
    fclose(file);
    qsort(records, *recordCount, sizeof(Record), compareRecords);
    return records;
}

int main() {
    const char *filePaths[] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt"};
    for (int i = 0; i < 5; i++) {
        int recordCount;
        Record *records = readAndSortKeyValueFile(filePaths[i], &recordCount);
        if (records) {
            for (int j = 0; j < recordCount; j++) {
                printf("%s=%s", records[j].key, records[j].value);
            }
            free(records);
        }
    }
    return 0;
}