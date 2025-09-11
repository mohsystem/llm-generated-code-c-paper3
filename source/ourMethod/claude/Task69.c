
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

int deleteFile(const char* filePath) {
    if (filePath == NULL || strlen(filePath) == 0) {
        fprintf(stderr, "File path cannot be null or empty\\n");
        return 0;
    }

    // Get absolute path
    char resolvedPath[PATH_MAX];
    if (realpath(filePath, resolvedPath) == NULL) {
        fprintf(stderr, "Error resolving path: %s\\n", strerror(errno));
        return 0;
    }

    // Check if file exists
    if (access(resolvedPath, F_OK) != 0) {
        fprintf(stderr, "File does not exist: %s\\n", resolvedPath);
        return 0;
    }

    // Check if it's a regular file
    FILE* fp = fopen(resolvedPath, "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open file: %s\\n", strerror(errno));
        return 0;
    }
    fclose(fp);

    // Delete the file
    if (remove(resolvedPath) != 0) {
        fprintf(stderr, "Error deleting file: %s\\n", strerror(errno));
        return 0;
    }

    return 1;
}

int main() {
    // Test cases
    const char* testPaths[] = {
        "test.txt",                    // Normal file
        "",                            // Empty path
        NULL,                          // Null path
        "../test.txt",                 // Path traversal attempt
        "nonexistent.txt",             // Non-existent file
        "/etc/passwd",                 // System file attempt
        "test/directory"               // Directory instead of file
    };

    int numTests = sizeof(testPaths) / sizeof(testPaths[0]);

    for (int i = 0; i < numTests; i++) {
        printf("\\nTesting path: %s\\n", testPaths[i] ? testPaths[i] : "NULL");
        int result = deleteFile(testPaths[i]);
        printf("Result: %d\\n", result);
    }

    return 0;
}
