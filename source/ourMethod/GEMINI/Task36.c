#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Reads a file and prints its content to standard output.
 *
 * @param filePath The path to the file to be read.
 */
void readFileAndPrint(const char* filePath) {
    // Rule #4 & #7: filePath is untrusted. We avoid TOCTOU by opening directly.
    FILE* file = fopen(filePath, "r");

    // Rule #8: Always check the return value of file operations.
    if (file == NULL) {
        // perror provides a descriptive error message from the OS.
        perror("Error opening file");
        return;
    }

    // Rule #1 & #2: Use a fixed-size buffer and safe functions to prevent overflows.
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Use fputs instead of printf with an uncontrolled format string.
        fputs(buffer, stdout);
    }

    // Check if the loop terminated because of an error rather than EOF.
    if (ferror(file)) {
        fprintf(stderr, "Error reading from file '%s'\n", filePath);
    }
    
    // Rule #8: Always close the file handle.
    if (fclose(file) != 0) {
        perror("Error closing file");
    }
}

/**
 * @brief Helper function to create a test file.
 */
void createTestFile(const char* fileName, const char* content) {
    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Failed to create test file");
        return;
    }
    if (fputs(content, file) == EOF) {
        fprintf(stderr, "Failed to write to test file '%s'\n", fileName);
    }
    fclose(file);
}

int main() {
    // Setup test files
    createTestFile("test1.txt", "Hello, World!");
    createTestFile("test2.txt", "This is line 1.\nThis is line 2.\n");
    createTestFile("test3.txt", "");
    createTestFile("test4.txt", "Some special characters: !@#$%^&*()\n");

    printf("--- Test Case 1: File with a single line ---\n");
    readFileAndPrint("test1.txt");
    printf("\n\n--- Test Case 2: File with multiple lines ---\n");
    readFileAndPrint("test2.txt");
    printf("\n--- Test Case 3: Empty file ---\n");
    readFileAndPrint("test3.txt");
    printf("\n--- Test Case 4: File with special characters ---\n");
    readFileAndPrint("test4.txt");
    printf("\n--- Test Case 5: Non-existent file ---\n");
    readFileAndPrint("nonexistent.txt");
    
    // Cleanup
    remove("test1.txt");
    remove("test2.txt");
    remove("test3.txt");
    remove("test4.txt");

    return 0;
}