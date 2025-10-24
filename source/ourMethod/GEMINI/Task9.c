#include <stdio.h>
#include <stddef.h> // For size_t

/**
 * @brief Determines if the sum of elements in an array is "odd" or "even".
 *
 * @param arr Pointer to the input array of integers.
 * @param size The number of elements in the array. An empty array (size 0) is treated as {0}.
 * @return "even" if the sum is even, "odd" otherwise.
 */
const char* oddOrEven(const int arr[], size_t size) {
    // Use long long for the sum to prevent potential integer overflow.
    long long sum = 0;
    for (size_t i = 0; i < size; ++i) {
        sum += arr[i];
    }
    
    if (sum % 2 == 0) {
        return "even";
    } else {
        return "odd";
    }
}

void print_array(const int arr[], size_t size) {
    printf("[");
    for (size_t i = 0; i < size; ++i) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]");
}

void run_test_case(const char* name, const int arr[], size_t size) {
    printf("%s:\n", name);
    printf("Input: ");
    print_array(arr, size);
    printf(" -> Output: \"%s\"\n", oddOrEven(arr, size));
    printf("--------------------\n");
}

int main() {
    // Test Case 1: Single zero
    int test1[] = {0};
    run_test_case("Test Case 1", test1, sizeof(test1) / sizeof(test1[0]));

    // Test Case 2: Mix of numbers, odd sum
    int test2[] = {0, 1, 4};
    run_test_case("Test Case 2", test2, sizeof(test2) / sizeof(test2[0]));

    // Test Case 3: Negative numbers, even sum
    int test3[] = {0, -1, -5};
    run_test_case("Test Case 3", test3, sizeof(test3) / sizeof(test3[0]));
    
    // Test Case 4: Empty array
    int test4_data[1]; // Dummy array to get a valid pointer
    run_test_case("Test Case 4", test4_data, 0);

    // Test Case 5: Sequence of numbers, odd sum
    int test5[] = {1, 2, 3, 4, 5};
    run_test_case("Test Case 5", test5, sizeof(test5) / sizeof(test5[0]));

    return 0;
}