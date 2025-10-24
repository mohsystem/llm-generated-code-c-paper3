#include <stdio.h>
#include <stddef.h>

/**
 * @brief Finds the integer that appears an odd number of times in an array.
 * It is guaranteed that exactly one such integer exists.
 * @param arr The input array of integers.
 * @param size The number of elements in the array.
 * @return The integer that appears an odd number of times.
 */
int findOdd(const int* arr, size_t size) {
    int result = 0;
    for (size_t i = 0; i < size; ++i) {
        result ^= arr[i];
    }
    return result;
}

void runTestCase(const char* name, const int* arr, size_t size) {
    printf("%s: [", name);
    for (size_t i = 0; i < size; ++i) {
        printf("%d%s", arr[i], (i == size - 1 ? "" : ", "));
    }
    printf("] -> %d\n", findOdd(arr, size));
}

int main() {
    // Test Case 1
    int arr1[] = {7};
    runTestCase("Test Case 1", arr1, sizeof(arr1) / sizeof(arr1[0]));

    // Test Case 2
    int arr2[] = {0};
    runTestCase("Test Case 2", arr2, sizeof(arr2) / sizeof(arr2[0]));

    // Test Case 3
    int arr3[] = {1, 1, 2};
    runTestCase("Test Case 3", arr3, sizeof(arr3) / sizeof(arr3[0]));

    // Test Case 4
    int arr4[] = {0, 1, 0, 1, 0};
    runTestCase("Test Case 4", arr4, sizeof(arr4) / sizeof(arr4[0]));

    // Test Case 5
    int arr5[] = {1, 2, 2, 3, 3, 3, 4, 3, 3, 3, 2, 2, 1};
    printf("Test Case 5: [1, 2, 2, ...] -> %d\n", findOdd(arr5, sizeof(arr5) / sizeof(arr5[0])));
    
    return 0;
}