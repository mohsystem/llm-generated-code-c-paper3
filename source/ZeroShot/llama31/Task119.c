#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseCSV(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        printf("Error opening file: %s\n", fileName);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char* cell = strtok(line, ",\n");
        while (cell) {
            printf("%s | ", cell);
            cell = strtok(NULL, ",\n");
        }
        printf("\n");
    }
    fclose(file);
}

int main() {
    const char* testCases[] = {
        "university_records.csv",
        "example.csv",
        "data.csv",
        "test.csv",
        "sample.csv"
    };

    for (int i = 0; i < 5; ++i) {
        parseCSV(testCases[i]);
    }

    return 0;
}