
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 4096

char* display_file_contents(const char* filename) {
    static char buffer[MAX_BUFFER];
    buffer[0] = '\\0';
    
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        snprintf(buffer, MAX_BUFFER, "Error: Unable to open file %s", filename);
        return buffer;
    }
    
    size_t total_read = 0;
    size_t bytes_read;
    while ((bytes_read = fread(buffer + total_read, 1, 
           MAX_BUFFER - total_read - 1, file)) > 0) {
        total_read += bytes_read;
        if (total_read >= MAX_BUFFER - 1) break;
    }
    
    buffer[total_read] = '\\0';
    fclose(file);
    return buffer;
}

int main() {
    const char* test_files[] = {
        "test1.txt",
        "sample.txt",
        "nonexistent.txt",
        "data.txt",
        "empty.txt"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Reading file: %s\\n", test_files[i]);
        printf("%s\\n", display_file_contents(test_files[i]));
        printf("------------------------\\n");
    }
    
    return 0;
}
