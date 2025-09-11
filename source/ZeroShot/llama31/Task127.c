#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFileAndWriteToTemp(const char* fileName) {
    FILE* reader = fopen(fileName, "r");
    if (reader == NULL) {
        fprintf(stderr, "File %s does not exist.\n", fileName);
        exit(EXIT_FAILURE);
    }

    FILE* writer = fopen(strcat(strdup(fileName), "temp_"), "w");
    if (writer == NULL) {
        fprintf(stderr, "Failed to open temporary file for writing.\n");
        fclose(reader);
        exit(EXIT_FAILURE);
    }

    char character;
    while ((character = fgetc(reader)) != EOF) {
        fputc(character, writer);
    }

    fclose(reader);
    fclose(writer);
}

int main() {
    const char* testCases[] = {
        "test1.txt",
        "test2.txt",
        "nonexistentfile.txt",
        "test3.txt",
        "test4.txt"
    };

    for (int i = 0; i < 5; ++i) {
        try {
            readFileAndWriteToTemp(testCases[i]);
            printf("File %s processed successfully.\n", testCases[i]);
        } catch (...) {
            // Note: C does not have try-catch blocks, so we handle errors manually.
            // Here we assume that if fopen or other functions fail, they will set errno.
            if (errno == ENOENT) {
                fprintf(stderr, "File %s does not exist.\n", testCases[i]);
            } else {
                fprintf(stderr, "An error occurred processing file %s.\n", testCases[i]);
            }
        }
    }

    return 0;
}