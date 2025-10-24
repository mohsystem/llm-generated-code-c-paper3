#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief Formats an array of 10 integers (0-9) into a phone number string.
 *
 * This function dynamically allocates memory for the result string.
 * The caller is responsible for freeing this memory using free().
 *
 * @param numbers A pointer to a constant array of integers.
 * @param count The number of elements in the array. Must be 10.
 * @return A pointer to the newly allocated string, or NULL if an error occurs
 *         (e.g., invalid input, memory allocation failure).
 */
char* createPhoneNumber(const int numbers[], size_t count) {
    if (numbers == NULL || count != 10) {
        return NULL; // Invalid input: null pointer or incorrect size
    }

    for (size_t i = 0; i < count; ++i) {
        if (numbers[i] < 0 || numbers[i] > 9) {
            return NULL; // Invalid input: number out of range
        }
    }

    // The format is "(XXX) XXX-XXXX" which is 14 chars + 1 for null terminator
    const size_t buffer_size = 15;
    char* phoneNumber = (char*)malloc(buffer_size);
    if (phoneNumber == NULL) {
        perror("Failed to allocate memory");
        return NULL; // Memory allocation failed
    }

    int written_chars = snprintf(phoneNumber, buffer_size, "(%d%d%d) %d%d%d-%d%d%d%d",
        numbers[0], numbers[1], numbers[2],
        numbers[3], numbers[4], numbers[5],
        numbers[6], numbers[7], numbers[8], numbers[9]);
    
    // Check if snprintf succeeded and wasn't truncated
    if (written_chars < 0 || (size_t)written_chars >= buffer_size) {
        free(phoneNumber); // Clean up on error
        return NULL; // Formatting error
    }

    return phoneNumber;
}

void run_test(const char* test_name, const int numbers[], size_t count) {
    printf("%s: { ", test_name);
    if (numbers != NULL) {
        for(size_t i = 0; i < count; ++i) {
            printf("%d%s", numbers[i], (i == count - 1 ? "" : ", "));
        }
    } else {
        printf("NULL");
    }
    printf(" }, count=%zu\n", count);
    
    char* result = createPhoneNumber(numbers, count);
    if (result != NULL) {
        printf("Result: %s\n", result);
        free(result); // Free the allocated memory
    } else {
        printf("Result: NULL (invalid input or memory error)\n");
    }
    printf("\n");
}

int main() {
    // Test Case 1: Valid input
    int test1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    run_test("Test 1", test1, 10);

    // Test Case 2: Another valid input
    int test2[] = {5, 5, 5, 1, 2, 3, 4, 5, 6, 7};
    run_test("Test 2", test2, 10);

    // Test Case 3: Invalid length (too short)
    int test3[] = {1, 2, 3};
    run_test("Test 3", test3, 3);
    
    // Test Case 4: Invalid number (out of range)
    int test4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, -1};
    run_test("Test 4", test4, 10);

    // Test Case 5: NULL input
    run_test("Test 5", NULL, 10);
    
    return 0;
}