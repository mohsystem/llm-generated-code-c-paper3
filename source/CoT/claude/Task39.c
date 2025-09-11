
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

char* display_file_contents(const char* filename) {
    if (filename == NULL || strlen(filename) == 0) {
        return strdup("Invalid filename");
    }
    
    char resolved_path[PATH_MAX];
    if (realpath(filename, resolved_path) == NULL) {
        return strdup("Invalid path");
    }
    
    // Security checks
    FILE* file = fopen(resolved_path, "r");
    if (file == NULL) {
        return strdup("Unable to open file");
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    
    if (file_size < 0) {
        fclose(file);
        return strdup("Error determining file size");
    }
    
    // Allocate memory for content
    char* content = (char*)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("Memory allocation error");
    }
    
    // Read file
    size_t read_size = fread(content, 1, file_size, file);
    fclose(file);
    
    if (read_size != (size_t)file_size) {
        free(content);
        return strdup("Error reading file");
    }
    
    content[file_size] = '\\0';
    return content;
}

int main() {
    // Test cases
    const char* test_files[] = {
        "test1.txt",
        "../test2.txt",  // Path traversal attempt
        "",             // Empty filename
        "nonexistent.txt",
        "/etc/passwd"   // Sensitive file access attempt
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Testing file: %s\\n", test_files[i]);
        char* result = display_file_contents(test_files[i]);
        printf("%s\\n", result);
        printf("------------------------\\n");
        free(result);
    }
    
    return 0;
}
