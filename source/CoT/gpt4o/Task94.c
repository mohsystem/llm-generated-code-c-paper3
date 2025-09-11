#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

typedef struct {
    char *key;
    char *value;
} Record;

int compareRecords(const void *a, const void *b) {
    Record *recordA = (Record *)a;
    Record *recordB = (Record *)b;
    return strcmp(recordA->key, recordB->key);
}

Record *readAndSortFile(const char *filename, size_t *recordCount) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    Record *records = NULL;
    char line[MAX_LINE_LENGTH];
    size_t count = 0;

    while (fgets(line, sizeof(line), file)) {
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "\n");

        if (key && value) {
            records = realloc(records, (count + 1) * sizeof(Record));
            records[count].key = strdup(key);
            records[count].value = strdup(value);
            count++;
        }
    }

    fclose(file);
    qsort(records, count, sizeof(Record), compareRecords);
    *recordCount = count;
    return records;
}

int main() {
    size_t recordCount;
    Record *sortedRecords = readAndSortFile("records.txt", &recordCount);
    if (sortedRecords) {
        for (size_t i = 0; i < recordCount; i++) {
            printf("%s=%s\n", sortedRecords[i].key, sortedRecords[i].value);
            free(sortedRecords[i].key);
            free(sortedRecords[i].value);
        }
        free(sortedRecords);
    }
    return 0;
}