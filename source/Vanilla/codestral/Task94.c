#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Record {
    char* key;
    char* value;
} Record;

int compareRecords(const void* a, const void* b) {
    return strcmp(((Record*)a)->key, ((Record*)b)->key);
}

Record* sortFileRecords(const char* fileName, int* numRecords) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    // Count the number of records
    int count = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        count++;
    }
    rewind(file);

    Record* records = malloc(count * sizeof(Record));
    if (records == NULL) {
        perror("Error allocating memory");
        exit(1);
    }

    int i = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        char* equalPos = strchr(buffer, '=');
        if (equalPos != NULL) {
            *equalPos = '\0';
            records[i].key = strdup(buffer);
            records[i].value = strdup(equalPos + 1);
            i++;
        }
    }

    fclose(file);
    *numRecords = count;
    qsort(records, count, sizeof(Record), compareRecords);
    return records;
}

int main() {
    int numRecords;
    Record* sortedRecords = sortFileRecords("records.txt", &numRecords);
    for (int i = 0; i < numRecords; i++) {
        printf("%s=%s", sortedRecords[i].key, sortedRecords[i].value);
    }
    for (int i = 0; i < numRecords; i++) {
        free(sortedRecords[i].key);
        free(sortedRecords[i].value);
    }
    free(sortedRecords);
    return 0;
}