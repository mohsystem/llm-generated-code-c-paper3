#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

char** readAndSortFile(const char* filePath, int* recordCount) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        perror("File not found.");
        *recordCount = 0;
        return NULL;
    }

    char** records = malloc(sizeof(char*) * 100);
    char line[MAX_LINE_LENGTH];
    *recordCount = 0;
    
    while (fgets(line, sizeof(line), file)) {
        if (strlen(line) > 1) {
            line[strcspn(line, "\n")] = 0;
            records[*recordCount] = strdup(line);
            (*recordCount)++;
        }
    }
    fclose(file);

    qsort(records, *recordCount, sizeof(char*), compare);
    return records;
}

int main() {
    int recordCount;
    char** sortedRecords = readAndSortFile("records.txt", &recordCount);
    for (int i = 0; i < recordCount; i++) {
        printf("%s\n", sortedRecords[i]);
        free(sortedRecords[i]);
    }
    free(sortedRecords);
    return 0;
}