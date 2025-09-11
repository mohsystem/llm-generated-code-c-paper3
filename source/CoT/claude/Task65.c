
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#define MAX_BUFFER 4096

char* readFile(const char* filename) {
    static char buffer[MAX_BUFFER];
    
    // Check for null or empty filename
    if (filename == NULL || strlen(filename) == 0) {
        return "Error: Filename cannot be null or empty";
    }

    // Validate filename format
    for (int i = 0; filename[i]; i++) {
        if (!isalnum(filename[i]) && filename[i] != '.' && 
            filename[i] != '_' && filename[i] != '-') {
            return "Error: Invalid filename format";
        }
    }

    // Check if file exists and is accessible
    struct stat st;
    if (stat(filename, &st) != 0) {
        return "Error: File does not exist";
    }

    // Try to open file
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return "Error: File is not accessible";
    }

    // Read file content
    size_t bytesRead = fread(buffer, 1, MAX_BUFFER - 1, file);
    buffer[bytesRead] = '\\0';
    fclose(file);

    if (bytesRead == 0) {
        return "Error: Unable to read file";
    }

    return buffer;
}

int main() {
    // Test cases
    const char* testFiles[] = {
        "test.txt",           // Normal case
        "",                   // Empty filename
        "invalid*file.txt",   // Invalid format
        "nonexistent.txt",    // Non-existent file
        "noaccess.txt"        // No access file
    };

    for (int i = 0; i < 5; i++) {
        printf("Testing file: %s\\n", testFiles[i]);
        printf("%s\\n", readFile(testFiles[i]));
        printf("-------------------\\n");
    }

    return 0;
}
