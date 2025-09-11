
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_BUFFER 4096

char* readFile(const char* filePath) {
    if (filePath == NULL || strlen(filePath) == 0) {
        fprintf(stderr, "File path cannot be null or empty\\n");
        return NULL;
    }

    // Open file
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        fprintf(stderr, "Cannot open file: %s (%s)\\n", 
                filePath, strerror(errno));
        return NULL;
    }

    // Get file size
    if (fseek(file, 0, SEEK_END) != 0) {
        fprintf(stderr, "Error seeking file: %s\\n", strerror(errno));
        fclose(file);
        return NULL;
    }
    long fileSize = ftell(file);
    if (fileSize == -1) {
        fprintf(stderr, "Error getting file size: %s\\n", strerror(errno));
        fclose(file);
        return NULL;
    }
    rewind(file);

    // Allocate memory for content
    char* buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\\n");
        fclose(file);
        return NULL;
    }

    // Read file content
    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if (bytesRead < (size_t)fileSize) {
        fprintf(stderr, "Error reading file: %s\\n", strerror(errno));
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[fileSize] = '\\0';
    fclose(file);
    return buffer;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filepath>\\n", argv[0]);
        return 1;
    }

    char* content = readFile(argv[1]);
    if (content == NULL) {
        return 1;
    }

    printf("File content:\\n%s\\n", content);
    free(content);
    return 0;
}
