#include <stdio.h>
#include <stddef.h>

/**
 * @brief Finds the missing letter in an array of consecutive (increasing) letters.
 *
 * @param arr An array of consecutive letters with one letter missing.
 * @param size The number of elements in the array.
 * @return The missing letter.
 */
char findMissingLetter(const char arr[], size_t size) {
    for (size_t i = 1; i < size; ++i) {
        // Check if the current character is not the expected next character
        if (arr[i] != arr[i - 1] + 1) {
            // If not, the missing character is the one after the previous character
            return (char)(arr[i - 1] + 1);
        }
    }
    // This part should be unreachable given the problem constraints
    // (always exactly one letter missing in an array of length >= 2).
    return '\0';
}

// Helper function to print an array of chars for test output
void printArray(const char arr[], size_t size) {
    printf("['");
    for (size_t i = 0; i < size; ++i) {
        printf("%c", arr[i]);
        if (i < size - 1) {
            printf("','");
        }
    }
    printf("']");
}

int main() {
    // Test Case 1
    char test1[] = {'a', 'b', 'c', 'd', 'f'};
    size_t size1 = sizeof(test1) / sizeof(test1[0]);
    printf("Test 1: ");
    printArray(test1, size1);
    printf(" -> %c\n", findMissingLetter(test1, size1));

    // Test Case 2
    char test2[] = {'O', 'Q', 'R', 'S'};
    size_t size2 = sizeof(test2) / sizeof(test2[0]);
    printf("Test 2: ");
    printArray(test2, size2);
    printf(" -> %c\n", findMissingLetter(test2, size2));

    // Test Case 3
    char test3[] = {'x', 'z'};
    size_t size3 = sizeof(test3) / sizeof(test3[0]);
    printf("Test 3: ");
    printArray(test3, size3);
    printf(" -> %c\n", findMissingLetter(test3, size3));

    // Test Case 4
    char test4[] = {'A', 'B', 'D'};
    size_t size4 = sizeof(test4) / sizeof(test4[0]);
    printf("Test 4: ");
    printArray(test4, size4);
    printf(" -> %c\n", findMissingLetter(test4, size4));

    // Test Case 5
    char test5[] = {'m', 'n', 'o', 'q', 'r'};
    size_t size5 = sizeof(test5) / sizeof(test5[0]);
    printf("Test 5: ");
    printArray(test5, size5);
    printf(" -> %c\n", findMissingLetter(test5, size5));

    return 0;
}