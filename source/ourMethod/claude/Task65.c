
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <sys/stat.h>

#define MAX_BUFFER 4096

char* read_file(const char* filename) {
    // Validate filename is not null or empty
    if (filename == NULL || strlen(filename) == 0) {
        return strdup("Error: Invalid filename - filename cannot be null or empty");
    }

    // Get absolute path
    char abs_path[PATH_MAX];
    if (realpath(filename, abs_path) == NULL) {
        return strdup("Error: Invalid filename format");
    }

    // Validate file exists and is accessible
    struct stat st;
    if (stat(abs_path, &st) != 0) {
        return strdup("Error: File does not exist");
    }
    if (!S_ISREG(st.st_mode)) {
        return strdup("Error: Path is not a regular file");  
    }
    if (access(abs_path, R_OK) != 0) {
        return strdup("Error: File is not readable");
    }

    // Open file
    FILE* file = fopen(abs_path, "r");
    if (file == NULL) {
        char error[100];
        snprintf(error, sizeof(error), "Error: Failed to open file - %s", strerror(errno));
        return strdup(error);
    }

    // Allocate buffer for contents
    char* buffer = malloc(MAX_BUFFER);
    if (buffer == NULL) {
        fclose(file);
        return strdup("Error: Memory allocation failed");
    }
    
    // Read file contents
    size_t bytes_read = fread(buffer, 1, MAX_BUFFER-1, file);
    if (ferror(file)) {
        free(buffer);
        fclose(file);
        return strdup("Error: Failed to read file");
    }

    buffer[bytes_read] = '\\0';
    fclose(file);
    
    return buffer;
}

int main() {
    // Test cases
    const char* test_files[] = {
        NULL,                   // Test null filename
        "",                     // Test empty filename
        "nonexistent.txt",      // Test non-existent file 
        "/etc/passwd",          // Test unauthorized access
        "../../test.txt",       // Test path traversal
        "test.txt",            // Test valid file
        NULL
    };

    for (int i = 0; test_files[i] != NULL; i++) {
        printf("\\nTesting file: %s\\n", test_files[i] ? test_files[i] : "NULL");
        char* result = read_file(test_files[i]);
        printf("%s\\n", result);
        free(result);
    }

    return 0;
}
