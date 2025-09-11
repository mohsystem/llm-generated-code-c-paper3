#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "File not found or could not be opened: %s\n", filename);
        return;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: ./Task65 <filename>\n");
        return 1;
    }
    const char* filename = argv[1];
    readFile(filename);

    // Test cases
    const char* testFiles[] = {"existingFile.txt", "nonExistingFile.txt", "invalidFile", "", NULL};
    for (const char* file : testFiles) {
        if (file != NULL) {
            printf("Testing with file: %s\n", file);
            readFile(file);
        } else {
            printf("File is null.\n");
        }
    }

    return 0;
}