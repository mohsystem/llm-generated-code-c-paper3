#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming a maximum file size and line length for simplicity.
// In real-world applications, use dynamic memory allocation.
#define MAX_FILE_SIZE 1024 * 1024
#define MAX_LINE_LENGTH 256

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file: %s\n", filename);
        return NULL;
    }

    char* file_content = (char*)malloc(MAX_FILE_SIZE);
    if (file_content == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    size_t total_bytes_read = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        size_t line_length = strlen(line);

        if (total_bytes_read + line_length >= MAX_FILE_SIZE) {
            fprintf(stderr, "Error: File too large.\n");
            fclose(file);
            free(file_content);
            return NULL;
        }
        strcpy(file_content + total_bytes_read, line);
        total_bytes_read += line_length;
    }

    fclose(file);
    return file_content;

}

int main() {
    // Test Cases

    printf("Test case 1:\n");
    char* result1 = read_file("test.txt");
    if (result1 != NULL) {
        printf("%s", result1);
        free(result1);
    }

    printf("\nTest case 2:\n");
    char* result2 = read_file("nonexistent.txt");
    if (result2 != NULL) {
        printf("%s", result2);
        free(result2);
    }

    printf("\nTest case 3:\n");
    char* result3 = read_file("../test.txt");
    if (result3 != NULL) {
        printf("%s", result3);
        free(result3);
    }


    printf("\nTest case 4:\n");
    char* result4 = read_file("test/../test.txt");
    if (result4 != NULL) {
        printf("%s", result4);
        free(result4);
    }

        printf("\nTest case 5:\n");
    char* result5 = read_file("....//test.txt");
    if (result5 != NULL) {
        printf("%s", result5);
        free(result5);
    }


    return 0;
}