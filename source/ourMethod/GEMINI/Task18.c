#include <stdio.h>
#include <stddef.h>

/**
 * @brief Given an array of ones and zeroes, convert the equivalent binary value to an integer.
 * 
 * @param binary A pointer to a constant array of integers (0s and 1s).
 * @param size The number of elements in the array.
 * @return The integer representation of the binary value.
 */
int binaryArrayToInteger(const int* binary, size_t size) {
    if (binary == NULL) {
        return 0;
    }
    int number = 0;
    for (size_t i = 0; i < size; ++i) {
        // Left shift the current number by 1 and add the new bit.
        number = (number << 1) | binary[i];
    }
    return number;
}

void run_test(const int* arr, size_t size, const char* label) {
    printf("Testing: %s ==> %d\n", label, binaryArrayToInteger(arr, size));
}

int main() {
    // Test Case 1
    int test1[] = {0, 0, 0, 1};
    run_test(test1, sizeof(test1) / sizeof(test1[0]), "[0, 0, 0, 1]");

    // Test Case 2
    int test2[] = {0, 0, 1, 0};
    run_test(test2, sizeof(test2) / sizeof(test2[0]), "[0, 0, 1, 0]");

    // Test Case 3
    int test3[] = {0, 1, 0, 1};
    run_test(test3, sizeof(test3) / sizeof(test3[0]), "[0, 1, 0, 1]");

    // Test Case 4
    int test4[] = {1, 0, 0, 1};
    run_test(test4, sizeof(test4) / sizeof(test4[0]), "[1, 0, 0, 1]");

    // Test Case 5
    int test5[] = {1, 1, 1, 1};
    run_test(test5, sizeof(test5) / sizeof(test5[0]), "[1, 1, 1, 1]");

    return 0;
}