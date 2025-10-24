#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>

// Rule #1: Define constants for validation rules.
#define MIN_AGE 0
#define MAX_AGE 120
#define MIN_NAME_LEN 2
#define MAX_NAME_LEN 50
#define OUTPUT_BUFFER_SIZE 256

/**
 * Validates a name string for length and character content (alpha and space).
 * @param name The name string to validate.
 * @return True if valid, false otherwise.
 */
bool isValidName(const char* name) {
    if (name == NULL) {
        return false;
    }
    size_t len = strlen(name);
    if (len < MIN_NAME_LEN || len > MAX_NAME_LEN) {
        return false;
    }
    for (size_t i = 0; i < len; ++i) {
        if (!isalpha((unsigned char)name[i]) && !isspace((unsigned char)name[i])) {
            return false;
        }
    }
    return true;
}

/**
 * Processes user input, validates it, and writes a result or error to a buffer.
 * @param name The user's name.
 * @param ageStr The user's age as a string.
 * @param output_buffer The buffer to write the result to.
 * @param buffer_size The size of the output buffer.
 */
void processUserInput(const char* name, const char* ageStr, char* output_buffer, size_t buffer_size) {
    // Rule #3: Ensure buffer operations are safe. Initialize buffer.
    if (buffer_size > 0) {
        output_buffer[0] = '\0';
    }

    // Rule #1 & #6: Validate all input and treat it as untrusted.
    if (!isValidName(name)) {
        snprintf(output_buffer, buffer_size, "Error: Invalid name. Name must be %d-%d letters and spaces.", MIN_NAME_LEN, MAX_NAME_LEN);
        return;
    }
    
    if (ageStr == NULL) {
        snprintf(output_buffer, buffer_size, "Error: Age string is null.");
        return;
    }

    // Rule #2 & #6: Use safer functions (strtol instead of atoi/sscanf).
    char* endptr;
    errno = 0; // Reset errno before the call.
    long age = strtol(ageStr, &endptr, 10);

    // Check for conversion errors.
    if (endptr == ageStr) {
        snprintf(output_buffer, buffer_size, "Error: Invalid age format. Not a number.");
        return;
    }
    if (*endptr != '\0') {
        snprintf(output_buffer, buffer_size, "Error: Invalid age format. Contains non-numeric characters.");
        return;
    }
    if (errno == ERANGE) {
        snprintf(output_buffer, buffer_size, "Error: Age is out of the valid integer range.");
        return;
    }

    // Rule #1: Validate range.
    if (age < MIN_AGE || age > MAX_AGE) {
        snprintf(output_buffer, buffer_size, "Error: Invalid age. Age must be between %d and %d.", MIN_AGE, MAX_AGE);
        return;
    }

    // Operation on validated data
    time_t t = time(NULL);
    // Note: localtime is not thread-safe. Use platform-specific alternatives for MT apps.
    struct tm* tm_info = localtime(&t);
    if (tm_info == NULL) {
        snprintf(output_buffer, buffer_size, "Error: Could not determine the current year.");
        return;
    }
    int currentYear = 1900 + tm_info->tm_year;
    int birthYear = currentYear - (int)age;

    // Rule #3 & #6: Use snprintf for safe, bounded string formatting.
    snprintf(output_buffer, buffer_size, "Hello, %s! You are %ld years old. You were likely born in %d.", 
             name, age, birthYear);
}


int main() {
    char result[OUTPUT_BUFFER_SIZE];
    
    printf("--- Running Test Cases ---\n");

    // Test Case 1: Valid input
    printf("Test 1 (Valid):\n");
    printf("Input: name='Alice', age='30'\n");
    processUserInput("Alice", "30", result, sizeof(result));
    printf("Output: %s\n\n", result);

    // Test Case 2: Invalid name (too short)
    printf("Test 2 (Invalid Name - Length):\n");
    printf("Input: name='J', age='25'\n");
    processUserInput("J", "25", result, sizeof(result));
    printf("Output: %s\n\n", result);

    // Test Case 3: Invalid name (contains numbers)
    printf("Test 3 (Invalid Name - Chars):\n");
    printf("Input: name='Bob123', age='40'\n");
    processUserInput("Bob123", "40", result, sizeof(result));
    printf("Output: %s\n\n", result);

    // Test Case 4: Invalid age (not a number)
    printf("Test 4 (Invalid Age - Format):\n");
    printf("Input: name='Charlie', age='twenty'\n");
    processUserInput("Charlie", "twenty", result, sizeof(result));
    printf("Output: %s\n\n", result);

    // Test Case 5: Invalid age (out of range)
    printf("Test 5 (Invalid Age - Range):\n");
    printf("Input: name='David', age='150'\n");
    processUserInput("David", "150", result, sizeof(result));
    printf("Output: %s\n\n", result);

    return 0;
}