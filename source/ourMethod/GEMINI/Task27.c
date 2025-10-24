#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/**
 * @brief Finds the outlier number in an array where all numbers are either even or odd, except for one.
 * 
 * @param arr The input array of integers.
 * @param size The number of elements in the array. Must be at least 3.
 * @return The outlier integer. Exits with failure if preconditions are not met.
 */
int findOutlier(const int* arr, size_t size) {
    if (arr == NULL || size < 3) {
        fprintf(stderr, "Error: Array must be non-null and contain at least 3 elements.\n");
        exit(EXIT_FAILURE);
    }

    int even_count = 0;
    // Check the parity of the first three elements to determine the majority.
    for (size_t i = 0; i < 3; ++i) {
        if (arr[i] % 2 == 0) {
            even_count++;
        }
    }

    bool majority_is_even = even_count >= 2;

    // Iterate through the array to find the number with the minority parity.
    for (size_t i = 0; i < size; ++i) {
        if (majority_is_even) {
            // If the majority is even, the outlier is odd.
            if (arr[i] % 2 != 0) {
                return arr[i];
            }
        } else {
            // If the majority is odd, the outlier is even.
            if (arr[i] % 2 == 0) {
                return arr[i];
            }
        }
    }
    
    // This part should be unreachable based on the problem description.
    fprintf(stderr, "Error: No outlier found, which violates problem constraints.\n");
    exit(EXIT_FAILURE);
}

int main(void) {
    // Test Case 1: Outlier is odd
    int test1[] = {2, 4, 0, 100, 4, 11, 2602, 36};
    size_t size1 = sizeof(test1) / sizeof(test1[0]);
    printf("Test 1 Result: %d\n", findOutlier(test1, size1));

    // Test Case 2: Outlier is even
    int test2[] = {160, 3, 1719, 19, 11, 13, -21};
    size_t size2 = sizeof(test2) / sizeof(test2[0]);
    printf("Test 2 Result: %d\n", findOutlier(test2, size2));

    // Test Case 3: Minimal array, outlier is even
    int test3[] = {1, 1, 2};
    size_t size3 = sizeof(test3) / sizeof(test3[0]);
    printf("Test 3 Result: %d\n", findOutlier(test3, size3));

    // Test Case 4: Negative numbers involved, outlier is odd
    int test4[] = {2, 6, 8, -10, 3};
    size_t size4 = sizeof(test4) / sizeof(test4[0]);
    printf("Test 4 Result: %d\n", findOutlier(test4, size4));
    
    // Test Case 5: Edge values, outlier is odd (INT_MAX)
    int test5[] = {INT_MAX, 0, 2};
    size_t size5 = sizeof(test5) / sizeof(test5[0]);
    printf("Test 5 Result: %d\n", findOutlier(test5, size5));

    return 0;
}