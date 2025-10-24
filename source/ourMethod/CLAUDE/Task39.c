#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_FILENAME_LEN 255
#define BUFFER_SIZE 4096

/* Validates that the filename contains only safe characters */
bool isValidFilename(const char *filename) {
    size_t len;
    const char *dangerous = "|&;$`\n<>()[]{}*?!~'\"";

    /* Check NULL pointer */
    if (filename == NULL) {
        return false;
    }

    /* Check length: must be non-empty and not exceed limit */
    len = strlen(filename);
    if (len == 0 || len > MAX_FILENAME_LEN) {
        return false;
    }

    /* Reject absolute paths and directory traversal */
    if (strstr(filename, "..") != NULL ||
        strchr(filename, '/') != NULL ||
        strchr(filename, '\\') != NULL ||
        filename[0] == '.' ||
        (len > 1 && filename[1] == ':')) { /* Windows drive letter */
        return false;
    }

    /* Reject shell metacharacters and control characters */
    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)filename[i];
        if (strchr(dangerous, (int)c) != NULL || c < 32 || c == 127) {
            return false;
        }
    }

    return true;
}

/* Safely reads and displays file contents without using system commands */
bool displayFileContents(const char *filename) {
    FILE *file = NULL;
    char *buffer = NULL;
    size_t bytesRead;
    bool success = false;

    /* Allocate buffer */
    buffer = (char *)malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return false;
    }

    /* Open file in binary read mode */
    file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file '%s'\n", filename);
        free(buffer);
        return false;
    }

    /* Read and display contents safely */
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        /* Write to stdout with bounds checking */
        if (fwrite(buffer, 1, bytesRead, stdout) != bytesRead) {
            fprintf(stderr, "Error: Failed to write output\n");
            goto cleanup;
        }
    }

    /* Check for read errors */
    if (ferror(file)) {
        fprintf(stderr, "Error: Failed to read file\n");
        goto cleanup;
    }

    success = true;

cleanup:
    /* Clean up resources */
    if (file != NULL) {
        fclose(file);
    }
    if (buffer != NULL) {
        free(buffer);
    }

    return success;
}

int main(void) {
    const char *testCases[] = {
        "test1.txt",
        "test2.txt",
        "test3.txt",
        "test4.txt",
        "test5.txt"
    };
    size_t numTests = sizeof(testCases) / sizeof(testCases[0]);
    char filename[MAX_FILENAME_LEN + 1];
    FILE *testFile = NULL;

    /* Create test files for demonstration */
    for (size_t i = 0; i < numTests; i++) {
        testFile = fopen(testCases[i], "w");
        if (testFile != NULL) {
            fprintf(testFile, "Test content for file %zu\n", i + 1);
            fclose(testFile);
            testFile = NULL;
        }
    }

    printf("=== Running Test Cases ===\n");
    for (size_t i = 0; i < numTests; i++) {
        printf("\n--- Testing file: %s ---\n", testCases[i]);

        /* Validate filename before processing */
        if (!isValidFilename(testCases[i])) {
            fprintf(stderr, "Error: Invalid filename '%s'\n", testCases[i]);
            continue;
        }

        /* Display contents safely without system commands */
        if (!displayFileContents(testCases[i])) {
            fprintf(stderr, "Failed to display file contents\n");
        }
    }

    printf("\n\n=== Interactive Mode ===\n");
    printf("Enter filename to display (or 'quit' to exit): ");

    /* Read filename with safe input handling */
    while (fgets(filename, sizeof(filename), stdin) != NULL) {
        size_t len;

        /* Remove trailing newline */
        len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n') {
            filename[len - 1] = '\0';
            len--;
        }

        /* Check for quit command */
        if (strcmp(filename, "quit") == 0) {
            break;
        }

        /* Validate input filename */
        if (!isValidFilename(filename)) {
            fprintf(stderr, "Error: Invalid filename. Filenames must:\n");
            fprintf(stderr, "  - Be 1-255 characters\n");
            fprintf(stderr, "  - Not contain path separators or '..'\n");
            fprintf(stderr, "  - Not contain shell metacharacters\n");
            printf("\nEnter filename to display (or 'quit' to exit): ");
            continue;
        }

        /* Display file contents using safe file I/O */
        displayFileContents(filename);

        printf("\nEnter filename to display (or 'quit' to exit): ");
    }

    return 0;
}
