
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_BUFFER 4096

char* readFile(const char* filePath) {
    static char buffer[MAX_BUFFER];
    FILE* file;
    size_t bytesRead;
    
    // Clear buffer
    memset(buffer, 0, MAX_BUFFER);
    
    // Security check for NULL
    if (filePath == NULL) {
        snprintf(buffer, MAX_BUFFER, "Invalid file path");
        return buffer;
    }
    
    // Open file
    file = fopen(filePath, "r");
    if (file == NULL) {
        snprintf(buffer, MAX_BUFFER, "Error opening file: %s", strerror(errno));
        return buffer;
    }
    
    // Read file
    bytesRead = fread(buffer, 1, MAX_BUFFER - 1, file);
    if (bytesRead == 0 && !feof(file)) {
        snprintf(buffer, MAX_BUFFER, "Error reading file: %s", strerror(errno));
    }
    
    // Close file
    fclose(file);
    return buffer;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Please provide file path as argument\\n");
        return 1;
    }

    // Test cases
    const char* testFiles[] = {
        argv[1],          // User provided path
        "test1.txt",      // Normal file
        "../test2.txt",   // Parent directory access
        "nonexistent.txt",// Non-existent file
        "/etc/passwd"     // System file access attempt
    };

    for (int i = 0; i < 5; i++) {
        printf("Reading file: %s\\n", testFiles[i]);
        printf("%s\\n", readFile(testFiles[i]));
        printf("------------------------\\n");
    }

    return 0;
}
