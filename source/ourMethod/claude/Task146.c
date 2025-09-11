
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to validate the array
bool validate_array(const int* arr, int size) {
    if (arr == NULL || size <= 0) {
        return false;
    }
    
    // Check if numbers are within valid range
    for (int i = 0; i < size; i++) {
        if (arr[i] <= 0 || arr[i] > size + 1) {
            return false;
        }
    }
    return true;
}

int find_missing_number(const int* arr, int size, int* error) {
    *error = 0;
    
    // Validate input
    if (!validate_array(arr, size)) {
        *error = 1;
        return -1;
    }
    
    // Length of array is n-1, where n is the expected range
    long long n = size + 1;
    
    // Calculate expected sum using formula: n*(n+1)/2
    long long expected_sum = n * (n + 1) / 2;
    
    // Calculate actual sum
    long long actual_sum = 0;
    for (int i = 0; i < size; i++) {
        actual_sum += arr[i];
    }
    
    // The difference is the missing number
    return (int)(expected_sum - actual_sum);
}

int main() {
    // Test cases
    int test1[] = {1, 2, 4, 5};
    int test2[] = {1, 2, 3, 5};
    int test3[] = {2, 3, 4, 5};
    int test4[] = {1, 3, 4};
    int test5[] = {1, 2, 3, 4, 6, 7, 8};
    
    int* test_arrays[] = {test1, test2, test3, test4, test5};
    int test_sizes[] = {4, 4, 4, 3, 7};
    
    for (int i = 0; i < 5; i++) {
        int error;
        int result = find_missing_number(test_arrays[i], test_sizes[i], &error);
        
        if (error) {
            printf("Test case %d failed: Invalid input\\n", i + 1);
        } else {
            printf("Test case %d: Missing number is %d\\n", i + 1, result);
        }
    }
    
    return 0;
}
