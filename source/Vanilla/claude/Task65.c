
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUFFER 1024

char* readFile(const char* filename) {
    static char buffer[MAX_BUFFER];
    
    if (filename == NULL || strlen(filename) == 0) {
        strcpy(buffer, "Error: Invalid filename");
        return buffer;
    }

    if (access(filename, F_OK) == -1) {
        strcpy(buffer, "Error: File does not exist");
        return buffer;
    }

    if (access(filename, R_OK) == -1) {
        strcpy(buffer, "Error: File is not readable");
        return buffer;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        strcpy(buffer, "Error: Cannot open file");
        return buffer;
    }

    memset(buffer, 0, MAX_BUFFER);
    size_t bytesRead = fread(buffer, 1, MAX_BUFFER - 1, file);
    fclose(file);

    if (bytesRead == 0) {
        strcpy(buffer, "Error: Could not read file");
        return buffer;
    }

    return buffer;
}

int main() {
    // Test cases
    const char* testFiles[] = {
        "test1.txt",           // Non-existent file
        "",                    // Empty filename
        NULL,                  // NULL filename
        "/root/secret.txt",    // No permission file
        "sample.txt"           // Valid file (create this file for testing)
    };

    for (int i = 0; i < 5; i++) {
        printf("Testing filename: %s\\n", testFiles[i] ? testFiles[i] : "NULL");
        printf("%s\\n", readFile(testFiles[i]));
        printf("-------------------\\n");
    }

    return 0;
}
