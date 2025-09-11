
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define MAX_BUFFER_SIZE 4096

char* readFile(const char* filename) {
    static char buffer[MAX_BUFFER_SIZE];
    char resolved_path[PATH_MAX];
    char cwd[PATH_MAX];
    
    // Clear buffer
    memset(buffer, 0, MAX_BUFFER_SIZE);
    
    // Get current working directory
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        snprintf(buffer, MAX_BUFFER_SIZE, "Error getting current directory: %s", strerror(errno));
        return buffer;
    }
    
    // Resolve the full path
    if (realpath(filename, resolved_path) == NULL) {
        snprintf(buffer, MAX_BUFFER_SIZE, "Error resolving path: %s", strerror(errno));
        return buffer;
    }
    
    // Check if file is within current directory
    if (strncmp(resolved_path, cwd, strlen(cwd)) != 0) {
        return "Access denied - Cannot access files outside current directory";
    }
    
    // Open file
    FILE* file = fopen(resolved_path, "r");
    if (file == NULL) {
        snprintf(buffer, MAX_BUFFER_SIZE, "Error opening file: %s", strerror(errno));
        return buffer;
    }
    
    // Read file content
    size_t bytesRead = fread(buffer, 1, MAX_BUFFER_SIZE - 1, file);
    if (ferror(file)) {
        fclose(file);
        snprintf(buffer, MAX_BUFFER_SIZE, "Error reading file: %s", strerror(errno));
        return buffer;
    }
    
    buffer[bytesRead] = '\\0';
    fclose(file);
    return buffer;
}

int main() {
    // Test cases
    const char* test_files[] = {
        "test1.txt",
        "nonexistent.txt",
        "../test.txt",  // attempting to access parent directory
        "test2.txt",
        "test3.txt"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Reading file: %s\\n", test_files[i]);
        printf("%s\\n", readFile(test_files[i]));
        printf("------------------------\\n");
    }
    
    return 0;
}
