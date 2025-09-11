
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 4096

char* read_file(const char* filename) {
    static char buffer[MAX_BUFFER];
    FILE* file;
    size_t bytes_read = 0;
    
    // Clear buffer
    memset(buffer, 0, MAX_BUFFER);
    
    // Open file in read mode
    file = fopen(filename, "r");
    if (file == NULL) {
        snprintf(buffer, MAX_BUFFER, "Error: Unable to open file %s", filename);
        return buffer;
    }
    
    // Read file contents
    bytes_read = fread(buffer, 1, MAX_BUFFER - 1, file);
    if (bytes_read == 0 && !feof(file)) {
        fclose(file);
        snprintf(buffer, MAX_BUFFER, "Error reading file %s", filename);
        return buffer;
    }
    
    buffer[bytes_read] = '\\0';
    fclose(file);
    return buffer;
}

int main() {
    // Test cases
    const char* test_files[] = {
        "test1.txt",
        "nonexistent.txt",
        "../test2.txt",  // Testing path traversal
        "/test3.txt",
        "./test4.txt"
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Reading file: %s\\n", test_files[i]);
        printf("%s\\n", read_file(test_files[i]));
        printf("------------------------\\n");
    }
    
    return 0;
}
