#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Validates that the file path doesn't contain directory traversal patterns */
bool is_valid_file_path(const char *path) {
    size_t len;
    size_t i;

    /* Check for NULL pointer to prevent crashes */
    if (path == NULL) {
        return false;
    }

    len = strlen(path);

    /* Reject empty or overly long paths */
    if (len == 0 || len > 4096) {
        return false;
    }

    /* Check for null bytes in the middle of string (injection attempt) */
    for (i = 0; i < len; i++) {
        if (path[i] == '\0' && i < len - 1) {
            return false;
        }
    }

    /* Reject directory traversal patterns */
    if (strstr(path, "..") != NULL) {
        return false;
    }

    /* Reject absolute paths to prevent accessing system files */
    if (path[0] == '/' || (len > 1 && path[1] == ':')) {
        return false;
    }

    return true;
}

/* Safely reads file contents with memory limits to prevent resource exhaustion */
bool read_file_contents(const char *filename) {
    FILE *file = NULL;
    long file_size = 0;
    size_t bytes_read = 0;
    char buffer[4096];
    const long MAX_FILE_SIZE = 10 * 1024 * 1024; /* 10MB limit */

    /* Validate input path to prevent directory traversal (CWE-22) */
    if (!is_valid_file_path(filename)) {
        fprintf(stderr, "Error: Invalid file path\n");
        return false;
    }

    /* Open file in binary mode for safe reading, using "rb" mode */
    file = fopen(filename, "rb");

    /* Check if file opened successfully */
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file '%s'\n", filename);
        return false;
    }

    /* Get file size to validate before reading */
    if (fseek(file, 0, SEEK_END) != 0) {
        fprintf(stderr, "Error: Could not seek to end of file\n");
        fclose(file);
        return false;
    }

    file_size = ftell(file);
    if (file_size < 0) {
        fprintf(stderr, "Error: Could not determine file size\n");
        fclose(file);
        return false;
    }

    /* Validate file size to prevent resource exhaustion */
    if (file_size > MAX_FILE_SIZE) {
        fprintf(stderr, "Error: File too large (max 10MB)\n");
        fclose(file);
        return false;
    }

    /* Seek back to beginning */
    if (fseek(file, 0, SEEK_SET) != 0) {
        fprintf(stderr, "Error: Could not seek to beginning of file\n");
        fclose(file);
        return false;
    }

    /* Read and print file contents in chunks with boundary checks (CWE-119, CWE-120) */
    while (!feof(file) && !ferror(file)) {
        /* Clear buffer before reading to prevent data leakage */
        memset(buffer, 0, sizeof(buffer));

        /* Read with size limit to prevent buffer overflow */
        bytes_read = fread(buffer, 1, sizeof(buffer), file);

        /* Validate bytes read is within bounds */
        if (bytes_read > 0 && bytes_read <= sizeof(buffer)) {
            /* Write exact number of bytes read to prevent over-read */
            if (fwrite(buffer, 1, bytes_read, stdout) != bytes_read) {
                fprintf(stderr, "Error: Failed to write to stdout\n");
                fclose(file);
                return false;
            }
        }

        /* Check for read errors */
        if (ferror(file)) {
            fprintf(stderr, "Error: Failed to read file\n");
            fclose(file);
            return false;
        }
    }

    /* Ensure file is closed to prevent resource leak */
    fclose(file);
    return true;
}

int main(void) {
    FILE *test_file = NULL;

    /* Test case 1: Valid file */
    printf("=== Test 1: Reading valid file ===\n");
    test_file = fopen("test1.txt", "w");
    if (test_file != NULL) {
        fprintf(test_file, "Hello, World!\nThis is a test file.");
        fclose(test_file);
        read_file_contents("test1.txt");
        printf("\n\n");
    }

    /* Test case 2: Non-existent file */
    printf("=== Test 2: Non-existent file ===\n");
    read_file_contents("nonexistent.txt");
    printf("\n");

    /* Test case 3: Directory traversal attempt (should be rejected) */
    printf("=== Test 3: Directory traversal attempt ===\n");
    read_file_contents("../etc/passwd");
    printf("\n");

    /* Test case 4: Empty filename */
    printf("=== Test 4: Empty filename ===\n");
    read_file_contents("");
    printf("\n");

    /* Test case 5: File with special characters */
    printf("=== Test 5: File with numbers and underscores ===\n");
    test_file = fopen("test_file_123.txt", "w");
    if (test_file != NULL) {
        fprintf(test_file, "File with special characters in name.");
        fclose(test_file);
        read_file_contents("test_file_123.txt");
        printf("\n\n");
    }

    return 0;
}
