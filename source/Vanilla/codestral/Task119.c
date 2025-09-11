#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_TOKENS 100

void readCSV(const char* fileName, char*** data, int* rows, int* cols) {
    FILE* file = fopen(fileName, "r");
    if (!file) return;

    char line[MAX_LINE_LENGTH];
    *rows = 0;
    *cols = 0;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        (*rows)++;
        char* token = strtok(line, ",");
        int col = 0;

        while (token) {
            (*data)[*rows - 1][col++] = strdup(token);
            token = strtok(NULL, ",");
        }

        if (*cols == 0) *cols = col;
    }

    fclose(file);
}

int main() {
    char** data[MAX_TOKENS];
    int rows, cols;

    for (int i = 0; i < MAX_TOKENS; i++) {
        data[i] = malloc(MAX_TOKENS * sizeof(char*));
    }

    readCSV("path_to_your_file.csv", data, &rows, &cols);
    // Now you can process the data

    for (int i = 0; i < rows; i++) {
        free(data[i]);
    }

    return 0;
}