#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a maximum file path length to prevent potential buffer overflows
#define MAX_FILE_PATH 256

char* readFile(const char* filePath) {
    if (filePath == NULL || strlen(filePath) == 0) {
        fprintf(stderr, "File path cannot be null or empty.\n");
        return NULL;
    }

    // Check for path traversal vulnerability
     if (strstr(filePath, "..") != NULL || strstr(filePath, "./") != NULL || filePath[0] != '/') {
        fprintf(stderr, "Invalid file path.\n");
        return NULL;
    }



    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* fileContent = (char*)malloc(fileSize + 1); // Allocate memory for file content
    if (fileContent == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(fileContent, 1, fileSize, file);
    if (bytesRead != fileSize) {
        perror("Error reading file");
        free(fileContent); // Free allocated memory
        fclose(file);
        return NULL;
    }


    fileContent[fileSize] = '\0'; // Null-terminate the string
    fclose(file);
    return fileContent;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    char* content = readFile(argv[1]);
    if (content != NULL) {
        printf("%s", content);
        free(content); // Free allocated memory
    }

    return 0;
}