#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char* sanitizeFileName(const char* fileName) {
    char* sanitized = (char*)malloc(strlen(fileName) + 1);
    for (int i = 0; fileName[i]; i++) {
        sanitized[i] = (isalnum(fileName[i]) || fileName[i] == '.' || fileName[i] == '_' || fileName[i] == '-') ? fileName[i] : '_';
    }
    sanitized[strlen(fileName)] = '\0';
    return sanitized;
}

char* uploadFile(const char* fileName, const char* fileContent) {
    char* response = (char*)malloc(256);
    struct stat st = {0};
    if (stat("server_storage", &st) == -1) {
        mkdir("server_storage", 0700);
    }

    char* sanitizedFileName = sanitizeFileName(fileName);
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "server_storage/%s", sanitizedFileName);
    
    FILE* file = fopen(filePath, "wb");
    if (file) {
        fwrite(fileContent, sizeof(char), strlen(fileContent), file);
        fclose(file);
        snprintf(response, 256, "File uploaded successfully: %s", sanitizedFileName);
    } else {
        snprintf(response, 256, "Failed to upload file");
    }
    free(sanitizedFileName);
    return response;
}

int main() {
    // Test cases
    printf("%s\n", uploadFile("testfile1.txt", "This is a test file"));
    printf("%s\n", uploadFile("testfile2.txt", "Another test file"));
    printf("%s\n", uploadFile("special!file@name.txt", "File with special chars !@#$"));
    printf("%s\n", uploadFile("empty.txt", "Empty file"));
    printf("%s\n", uploadFile("longfile.txt", "File with long content"));

    return 0;
}