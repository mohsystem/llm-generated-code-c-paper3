// Note: C does not have built-in CSV parsing capabilities.
// This is a simplified version that assumes no commas in the data and no quoted fields.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 32

char** parseCSV(const char* filename, int* row_count, int* col_count) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    char line[MAX_LINE_LENGTH];
    int rows = 0;
    int cols = 0;

    // First pass to count rows and cols
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        rows++;
        char* token = strtok(line, ",");
        int curr_cols = 0;
        while (token) {
            curr_cols++;
            token = strtok(NULL, ",");
        }
        if (curr_cols > cols) cols = curr_cols;
    }
    rewind(file);

    char** result = malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        result[i] = malloc(cols * MAX_FIELD_LENGTH * sizeof(char));
    }

    // Second pass to fill result
    for (int i = 0; i < rows; i++) {
        fgets(line, MAX_LINE_LENGTH, file);
        char* token = strtok(line, ",");
        int j = 0;
        while (token) {
            strcpy(result[i] + (j * MAX_FIELD_LENGTH), token);
            token = strtok(NULL, ",");
            j++;
        }
    }

    fclose(file);
    *row_count = rows;
    *col_count = cols;
    return result;
}

void freeCSVData(char** data, int rows) {
    for (int i = 0; i < rows; i++) {
        free(data[i]);
    }
    free(data);
}

int main() {
    int rows, cols;
    char** data = parseCSV("example.csv", &rows, &cols);
    if (!data) {
        printf("Could not open file\n");
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%s ", data[i] + (j * MAX_FIELD_LENGTH));
        }
        printf("\n");
    }

    freeCSVData(data, rows);
    return 0;
}