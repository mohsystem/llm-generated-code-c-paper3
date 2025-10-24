#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Frees the memory allocated by numberLines.
 * @param lines The array of strings to free.
 * @param count The number of strings in the array.
 */
void freeNumberedLines(char** lines, size_t count) {
    if (lines == NULL) {
        return;
    }
    for (size_t i = 0; i < count; ++i) {
        free(lines[i]); // Free each individual string
    }
    free(lines); // Free the array of pointers
}

/**
 * @brief Prepends line numbers to an array of strings.
 * 
 * The caller is responsible for freeing the returned array and its contents
 * by calling freeNumberedLines.
 * 
 * @param lines An array of constant C-style strings.
 * @param count The number of strings in the array.
 * @return A newly allocated array of strings with line numbers, or NULL on failure or if count is 0.
 */
char** numberLines(const char* const* lines, size_t count) {
    if (count == 0) {
        return NULL; // Return NULL for empty input, caller should not dereference.
    }
    if (lines == NULL) {
        return NULL; // Invalid input
    }

    char** numbered_lines = malloc(count * sizeof(char*));
    if (numbered_lines == NULL) {
        perror("Failed to allocate memory for lines array");
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        const char* current_line = lines[i] ? lines[i] : ""; // Treat null line pointers as empty strings

        // Use snprintf with a NULL buffer to safely calculate the required buffer size.
        int required_size = snprintf(NULL, 0, "%zu: %s", i + 1, current_line);
        if (required_size < 0) {
            fprintf(stderr, "Encoding error on line %zu\n", i);
            freeNumberedLines(numbered_lines, i); // Cleanup partially allocated array
            return NULL;
        }

        // Allocate memory for the new string (+1 for null terminator).
        numbered_lines[i] = malloc((size_t)required_size + 1);
        if (numbered_lines[i] == NULL) {
            perror("Failed to allocate memory for a line");
            freeNumberedLines(numbered_lines, i); // Cleanup
            return NULL;
        }

        // Format the new string into the allocated buffer.
        int written_size = snprintf(numbered_lines[i], (size_t)required_size + 1, "%zu: %s", i + 1, current_line);
        if (written_size < 0 || written_size > required_size) {
            fprintf(stderr, "snprintf formatting error on line %zu\n", i);
            free(numbered_lines[i]); // Free the last failed allocation
            freeNumberedLines(numbered_lines, i); // Cleanup
            return NULL;
        }
    }

    return numbered_lines;
}

// Helper to print results for testing
void printResult(const char* caseName, char** result, size_t count) {
    printf("%s: [", caseName);
    if (result != NULL) {
        for (size_t i = 0; i < count; ++i) {
            printf("\"%s\"", result[i]);
            if (i < count - 1) {
                printf(", ");
            }
        }
    }
    printf("]\n");
}

int main() {
    // Test Case 1: Empty list
    const char* test1[] = {};
    size_t count1 = 0;
    char** result1 = numberLines(test1, count1);
    printResult("Test Case 1", result1, count1);
    freeNumberedLines(result1, count1);

    // Test Case 2: Basic list
    const char* test2[] = {"a", "b", "c"};
    size_t count2 = sizeof(test2) / sizeof(test2[0]);
    char** result2 = numberLines(test2, count2);
    printResult("Test Case 2", result2, count2);
    freeNumberedLines(result2, count2);

    // Test Case 3: List with empty strings
    const char* test3[] = {"first", "", "third"};
    size_t count3 = sizeof(test3) / sizeof(test3[0]);
    char** result3 = numberLines(test3, count3);
    printResult("Test Case 3", result3, count3);
    freeNumberedLines(result3, count3);
    
    // Test Case 4: Single element list
    const char* test4[] = {"single line"};
    size_t count4 = sizeof(test4) / sizeof(test4[0]);
    char** result4 = numberLines(test4, count4);
    printResult("Test Case 4", result4, count4);
    freeNumberedLines(result4, count4);

    // Test Case 5: List with a NULL string pointer inside
    const char* test5[] = {"line 1", NULL, "line 3"};
    size_t count5 = sizeof(test5) / sizeof(test5[0]);
    char** result5 = numberLines(test5, count5);
    printResult("Test Case 5", result5, count5);
    freeNumberedLines(result5, count5);

    return 0;
}