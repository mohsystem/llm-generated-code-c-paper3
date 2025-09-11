#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 1000
#define MAX_RECORD_LENGTH 100

void sortKeyValueRecords(const char* fileName) {
    char records[MAX_RECORDS][MAX_RECORD_LENGTH];
    int recordCount = 0;

    FILE* file = fopen(fileName, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", fileName);
        return;
    }

    char line[MAX_RECORD_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        strcpy(records[recordCount], line);
        recordCount++;
        if (recordCount >= MAX_RECORDS) break;
    }
    fclose(file);

    // Simple bubble sort for demonstration purposes
    for (int i = 0; i < recordCount - 1; i++) {
        for (int j = 0; j < recordCount - i - 1; j++) {
            if (strcmp(records[j], records[j + 1]) > 0) {
                char temp[MAX_RECORD_LENGTH];
                strcpy(temp, records[j]);
                strcpy(records[j], records[j + 1]);
                strcpy(records[j + 1], temp);
            }
        }
    }

    file = fopen(fileName, "w");
    if (!file) {
        fprintf(stderr, "Error opening file for writing: %s\n", fileName);
        return;
    }

    for (int i = 0; i < recordCount; i++) {
        fprintf(file, "%s\n", records[i]);
    }
    fclose(file);

    printf("Sorted records in %s:\n", fileName);
    for (int i = 0; i < recordCount; i++) {
        printf("%s\n", records[i]);
    }
}

int main() {
    const char* testFiles[] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt"};
    for (int i = 0; i < 5; i++) {
        sortKeyValueRecords(testFiles[i]);
    }
    return 0;
}