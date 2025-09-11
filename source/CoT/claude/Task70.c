
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#define MAX_BUFFER 4096

char* readFile(const char* filePath) {
    if (filePath == NULL || strlen(filePath) == 0) {
        return strdup("Invalid file path");
    }
    
    // Security checks
    struct stat st;
    if (stat(filePath, &st) != 0) {
        return strdup("File does not exist");
    }
    if (!S_ISREG(st.st_mode)) {
        return strdup("Not a regular file");
    }
    
    // Open file securely
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        char errMsg[256];
        snprintf(errMsg, sizeof(errMsg), "Error reading file: %s", strerror(errno));
        return strdup(errMsg);
    }
    
    // Read file content
    char* content = malloc(MAX_BUFFER);
    if (content == NULL) {
        fclose(file);
        return strdup("Memory allocation error");
    }
    
    size_t totalSize = 0;
    size_t bytesRead;
    char buffer[1024];
    
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        if (totalSize + bytesRead >= MAX_BUFFER - 1) {
            fclose(file);
            free(content);
            return strdup("File too large");
        }
        memcpy(content + totalSize, buffer, bytesRead);
        totalSize += bytesRead;
    }
    
    content[totalSize] = '\\0';
    fclose(file);
    return content;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Please provide file path as argument\\n");
        return 1;
    }
    
    // Test cases
    const char* testFiles[] = {
        argv[1],          // User provided file
        "test1.txt",      // Regular file
        "/etc/passwd",    // System file
        "../test2.txt",   // Parent directory file
        "nonexistent.txt" // Non-existent file
    };
    
    for (int i = 0; i < 5; i++) {
        printf("\\nReading file: %s\\n", testFiles[i]);
        char* content = readFile(testFiles[i]);
        printf("Content:\\n%s\\n", content);
        free(content);
    }
    
    return 0;
}
