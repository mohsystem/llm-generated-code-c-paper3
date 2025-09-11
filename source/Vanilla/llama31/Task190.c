#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void transposeFile(const char* inputFile, const char* outputFile) {
    FILE* reader = fopen(inputFile, "r");
    FILE* writer = fopen(outputFile, "w");

    if (!reader || !writer) {
        fprintf(stderr, "Failed to open file.\n");
        return;
    }

    char line[1024];
    int numColumns = 0;
    int numRows = 0;
    char** columns = NULL;

    // Read and count columns and rows
    while (fgets(line, sizeof(line), reader)) {
        char* field = strtok(line, " \n");
        int count = 0;
        while (field) {
            count++;
            field = strtok(NULL, " \n");
        }
        if (numColumns == 0) {
            numColumns = count;
            columns = malloc(numColumns * sizeof(char*));
            for (int i = 0; i < numColumns; i++) {
                columns[i] = malloc(1024 * sizeof(char));
                columns[i][0] = '\0';
            }
        }
        rewind(reader); // Reset file pointer for re-reading
        break;
    }

    // Read and transpose
    while (fgets(line, sizeof(line), reader)) {
        char* field = strtok(line, " \n");
        int colIndex = 0;
        while (field) {
            strcat(columns[colIndex], field);
            strcat(columns[colIndex], " ");
            field = strtok(NULL, " \n");
            colIndex++;
        }
        numRows++;
    }

    // Write transposed data
    for (int i = 0; i < numColumns; i++) {
        fprintf(writer, "%s\n", columns[i]);
        free(columns[i]);
    }
    free(columns);

    fclose(reader);
    fclose(writer);
}

int main() {
    // Test cases
    transposeFile("file.txt", "output.txt");
    // Additional test cases can be added here
    return 0;
}