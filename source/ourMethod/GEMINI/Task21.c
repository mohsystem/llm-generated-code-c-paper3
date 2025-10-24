#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/**
 * Given an array of integers, create a new array with the smallest value removed.
 * Does not mutate the original array.
 * If there are multiple elements with the same value, removes the one with the lowest index.
 * If the input array is empty, returns NULL and sets new_size to 0.
 *
 * @param numbers   Pointer to the constant input array.
 * @param n         The number of elements in the input array.
 * @param new_size  Pointer to an integer where the size of the new array will be stored.
 * @return          A pointer to the newly allocated array. The caller is responsible for freeing this memory.
 *                  Returns NULL if the input array is empty or memory allocation fails.
 */
int* removeSmallest(const int* numbers, size_t n, size_t* new_size) {
    if (numbers == NULL || n == 0) {
        *new_size = 0;
        return NULL;
    }

    int min_val = INT_MAX;
    size_t min_index = 0;

    for (size_t i = 0; i < n; ++i) {
        if (numbers[i] < min_val) {
            min_val = numbers[i];
            min_index = i;
        }
    }

    *new_size = n - 1;
    if (*new_size == 0) {
        // Return a special non-NULL pointer for an empty array if needed,
        // or just NULL. NULL is simpler.
        return NULL;
    }
    
    int* result = (int*)malloc((*new_size) * sizeof(int));
    if (result == NULL) {
        // Handle malloc failure
        *new_size = 0;
        return NULL;
    }

    for (size_t i = 0, j = 0; i < n; ++i) {
        if (i != min_index) {
            result[j++] = numbers[i];
        }
    }

    return result;
}

void print_array(const char* label, const int* arr, size_t n) {
    printf("%s", label);
    printf("[");
    for (size_t i = 0; i < n; ++i) {
        printf("%d%s", arr[i], (i == n - 1 ? "" : ", "));
    }
    printf("]\n");
}

void run_test_case(const char* name, const int* original, size_t n) {
    printf("%s\n", name);
    print_array("Original: ", original, n);
    
    size_t result_size;
    int* result = removeSmallest(original, n, &result_size);
    
    print_array("Result:   ", result, result_size);
    print_array("Original after call: ", original, n); // Verify original is not mutated
    
    free(result); // Caller must free the memory
    printf("\n");
}

int main() {
    // Test Case 1
    int tc1[] = {1, 2, 3, 4, 5};
    run_test_case("Test Case #1", tc1, 5);

    // Test Case 2
    int tc2[] = {5, 3, 2, 1, 4};
    run_test_case("Test Case #2", tc2, 5);

    // Test Case 3
    int tc3[] = {2, 2, 1, 2, 1};
    run_test_case("Test Case #3", tc3, 5);

    // Test Case 4
    int tc4[] = {42};
    run_test_case("Test Case #4", tc4, 1);

    // Test Case 5
    int tc5[] = {};
    run_test_case("Test Case #5", tc5, 0);

    return 0;
}