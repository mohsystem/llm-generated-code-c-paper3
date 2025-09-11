#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} Record;

int compareRecords(const void* a, const void* b) {
    Record* ra = (Record*)a;
    Record* rb = (Record*)b;
    return strcmp(ra->key, rb->key);
}

Record* readRecords(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return NULL;
    }

    int capacity = 10;
    Record* records = malloc(capacity * sizeof(Record));
    *count = 0;

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        char* equalsPos = strchr(line, '=');
        if (equalsPos) {
            *equalsPos = '\0';
            equalsPos++;
            if (*count < capacity) {
                records[*count].key = strdup(line);
                records[*count].value = strdup(equalsPos);
                (*count)++;
            } else {
                capacity *= 2;
                records = realloc(records, capacity * sizeof(Record));
                records[*count].key = strdup(line);
                records[*count].value = strdup(equalsPos);
                (*count)++;
            }
        } else {
            fprintf(stderr, "Skipping invalid record: %s\n", line);
        }
    }
    fclose(file);
    return records;
}

void sortRecords(Record* records, int count) {
    qsort(records, count, sizeof(Record), compareRecords);
}

void printRecords(Record* records, int count) {
    for (int i = 0; i < count; i++) {
        printf("%s=%s\n", records[i].key, records[i].value);
    }
}

void freeRecords(Record* records, int count) {
    for (int i = 0; i < count; i++) {
        free(records[i].key);
        free(records[i].value);
    }
    free(records);
}

int main() {
    const char* filename = "records.txt";
    int count;
    Record* records = readRecords(filename, &count);
    if (records) {
        sortRecords(records, count);
        printRecords(records, count);
        freeRecords(records, count);
    }
    return 0;
}