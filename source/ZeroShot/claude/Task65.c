
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BUFFER 4096

char* read_file(const char* filename) {
    static char result[MAX_BUFFER];
    
    if (filename == NULL || strlen(filename) == 0) {
        strcpy(result, "Invalid filename");
        return result;
    }

    // Check file extension
    const char* dot = strrchr(filename, '.');
    if (dot == NULL || 
        (strcmp(dot, ".txt") != 0 && 
         strcmp(dot, ".csv") != 0 && 
         strcmp(dot, ".dat") != 0)) {
        strcpy(result, "Invalid file format. Only txt, csv and dat files allowed");
        return result;
    }

    // Check for directory traversal
    if (strstr(filename, "..") != NULL || filename[0] == '/') {
        strcpy(result, "Invalid file path");
        return result;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        strcpy(result, "File cannot be accessed or does not exist");
        return result;
    }

    size_t bytes_read = 0;
    memset(result, 0, MAX_BUFFER);
    
    while (!feof(file) && bytes_read < MAX_BUFFER - 1) {
        size_t read = fread(result + bytes_read, 1, MAX_BUFFER - bytes_read - 1, file);
        if (read == 0 && ferror(file)) {
            fclose(file);
            strcpy(result, "Error reading file");
            return result;
        }
        bytes_read += read;
    }
    
    fclose(file);
    result[bytes_read] = '\\0';
    return result;
}

int main() {
    // Test cases
    const char* test_files[] = {
        "test.txt",
        "invalid.exe",
        "",
        "nonexistent.txt",
        "../attempt_traversal.txt"
    };

    for (int i = 0; i < 5; i++) {
        printf("Testing file: %s\\n", test_files[i]);
        printf("%s\\n", read_file(test_files[i]));
        printf("-------------------\\n");
    }

    return 0;
}
