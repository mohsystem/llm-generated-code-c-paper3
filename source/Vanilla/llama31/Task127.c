#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void readAndWriteToFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        perror("FileNotFoundError");
        exit(EXIT_FAILURE);
    }

    FILE* tempFile = tmpfile();
    if (tempFile == NULL) {
        perror("Failed to create temporary file");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    while (fread(buffer, 1, 1024, file) > 0) {
        fwrite(buffer, 1, 1024, tempFile);
    }
    fwrite(buffer, 1, fread(buffer, 1, 1024, file), tempFile);

    rewind(tempFile);
    while (fread(buffer, 1, 1024, tempFile) > 0) {
        fwrite(buffer, 1, 1024, stdout);
    }
    fwrite(buffer, 1, fread(buffer, 1, 1024, tempFile), stdout);

    fclose(file);
    fclose(tempFile);
}

int main() {
    const char* testFiles[] = {"existing_file.txt", "nonexistent_file.txt", "another_existing_file.txt", "yet_another_nonexistent_file.txt", "file_with_permissions_issue.txt"};

    for (int i = 0; i < 5; ++i) {
        try {
            readAndWriteToFile(testFiles[i]);
        } catch (...) {
            fprintf(stderr, "Error processing file %s: %s\n", testFiles[i], strerror(errno));
        }
    }

    return 0;
}