// task119.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseCSV(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", fileName);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ",\n");
        while (token) {
            printf("%s ", token);
            token = strtok(NULL, ",\n");
        }
        printf("\n");
    }

    fclose(file);
}

int main() {
    const char* testCases[] = {"test1.csv", "test2.csv", "test3.csv", "test4.csv", "test5.csv"};
    for (int i = 0; i < 5; ++i) {
        parseCSV(testCases[i]);
    }
    return 0;
}