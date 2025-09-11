#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void readFileAndWriteToTemp(const char* filePath) {
    FILE* inputFile = fopen(filePath, "rb");
    if (inputFile == NULL) {
        fprintf(stderr, "Error opening input file: %s - %s\n", filePath, strerror(errno));
        exit(EXIT_FAILURE);
    }

    char* tempFilePath = malloc(strlen(filePath) + 5);
    if (tempFilePath == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    sprintf(tempFilePath, "temp_%s", filePath);

    FILE* outputFile = fopen(tempFilePath, "wb");
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening output file: %s - %s\n", tempFilePath, strerror(errno));
        free(tempFilePath);
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, 1024, inputFile)) > 0) {
        if (fwrite(buffer, 1, bytesRead, outputFile) != bytesRead) {
            fprintf(stderr, "Error writing to output file: %s - %s\n", tempFilePath, strerror(errno));
            free(tempFilePath);
            fclose(inputFile);
            fclose(outputFile);
            exit(EXIT_FAILURE);
        }
    }

    free(tempFilePath);
    fclose(inputFile);
    fclose(outputFile);
}

int main() {
    const char* testCases[] = {
        "path/to/existing/file.txt",
        "path/to/non/existing/file.txt",
        "path/to/existing/directory",
        "path/to/existing/file_with_no_read_permission.txt",
        "path/to/existing/file_with_no_write_permission.txt"
    };

    for (size_t i = 0; i < sizeof(testCases) / sizeof(testCases[0]); ++i) {
        try {
            readFileAndWriteToTemp(testCases[i]);
        } catch (...) {
            fprintf(stderr, "Error processing file: %s\n", testCases[i]);
        }
    }

    return 0;
}