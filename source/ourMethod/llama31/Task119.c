#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseCSV(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ",");
        while (token) {
            printf("%s | ", token);
            token = strtok(NULL, ",");
        }
        printf("\n");
    }
    fclose(file);
}

int main() {
    const char* testFiles[] = {"test1.csv", "test2.csv", "test3.csv", "test4.csv", "test5.csv"};
    for (int i = 0; i < 5; i++) {
        parseCSV(testFiles[i]);
    }
    return 0;
}