
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int copy_file(const char* source_path, const char* dest_path) {
    FILE *src = NULL, *dst = NULL;
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    int success = 0;

    // Check for null or empty paths
    if (!source_path || !dest_path || !strlen(source_path) || !strlen(dest_path)) {
        fprintf(stderr, "Error: Invalid file paths\\n");
        return 0;
    }

    // Open source file
    src = fopen(source_path, "rb");
    if (!src) {
        fprintf(stderr, "Error opening source file: %s\\n", strerror(errno));
        return 0;
    }

    // Open destination file
    dst = fopen(dest_path, "wb");
    if (!dst) {
        fprintf(stderr, "Error opening destination file: %s\\n", strerror(errno));
        fclose(src);
        return 0;
    }

    // Copy file contents
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
        if (fwrite(buffer, 1, bytes_read, dst) != bytes_read) {
            fprintf(stderr, "Error writing to destination file: %s\\n", strerror(errno));
            success = 0;
            goto cleanup;
        }
    }

    if (ferror(src)) {
        fprintf(stderr, "Error reading from source file: %s\\n", strerror(errno));
        success = 0;
    } else {
        success = 1;
    }

cleanup:
    if (src) fclose(src);
    if (dst) fclose(dst);
    return success;
}

int main() {
    char temp_dir[256];
    char dest_path[512];
    
    // Get temporary directory
    #ifdef _WIN32
        strcpy(temp_dir, getenv("TEMP"));
    #else
        strcpy(temp_dir, "/tmp");
    #endif

    // Test cases
    // Test 1: Normal copy
    sprintf(dest_path, "%s/test1.txt", temp_dir);
    printf("Test 1: %d\\n", copy_file("test.txt", dest_path));

    // Test 2: Source file doesn't exist
    sprintf(dest_path, "%s/test2.txt", temp_dir);
    printf("Test 2: %d\\n", copy_file("nonexistent.txt", dest_path));

    // Test 3: Invalid source path
    sprintf(dest_path, "%s/test3.txt", temp_dir);
    printf("Test 3: %d\\n", copy_file("", dest_path));

    // Test 4: Invalid destination path
    printf("Test 4: %d\\n", copy_file("test.txt", ""));

    // Test 5: No write permission
    printf("Test 5: %d\\n", copy_file("test.txt", "/root/test5.txt"));

    return 0;
}
