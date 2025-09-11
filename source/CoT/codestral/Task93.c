#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_RECORDS 1000

struct Record {
    char key[MAX_LINE_LENGTH];
    char value[MAX_LINE_LENGTH];
};

int compareRecords(const void* a, const void* b) {
    return strcmp(((struct Record*)a)->key, ((struct Record*)b)->key);
}

int readAndSortFile(const char* fileName, struct Record records[]) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    int count = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char* pos = strchr(line, '=');
        if (pos != NULL) {
            strncpy(records[count].key, line, pos - line);
            records[count].key[pos - line] = '\0';
            strncpy(records[count].value, pos + 1, MAX_LINE_LENGTH - (pos - line) - 1);
            records[count].value[MAX_LINE_LENGTH - (pos - line) - 1] = '\0';
            count++;
        }
    }

    fclose(file);
    return count;
}

int main() {
    struct Record records[MAX_RECORDS];
    int count = readAndSortFile("records.txt", records);

    qsort(records, count, sizeof(struct Record), compareRecords);

    for (int i = 0; i < count; i++) {
        printf("%s=%s\n", records[i].key, records[i].value);
    }

    return 0;
}