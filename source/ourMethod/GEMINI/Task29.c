#include <stdio.h>
#include <stdlib.h>

// A structure to hold the pair of indices
typedef struct {
    size_t index1;
    size_t index2;
} Indices;

/**
 * Finds two different items in the array that sum up to the target value.
 * This implementation uses a brute-force O(n^2) approach for simplicity in C.
 *
 * @param numbers The input array of integers.
 * @param length The number of elements in the array.
 * @param target The target integer value.
 * @return An Indices struct containing the indices of the two numbers.
 */
Indices two_sum(const int* numbers, size_t length, int target) {
    for (size_t i = 0; i < length; ++i) {
        for (size_t j = i + 1; j < length; ++j) {
            if (numbers[i] + numbers[j] == target) {
                Indices result = {i, j};
                return result;
            }
        }
    }
    // Per problem description, a valid solution always exists.
    // Returning {-1, -1} is for a more general case where a solution might not be found.
    Indices not_found = {(size_t)-1, (size_t)-1};
    return not_found;
}

void run_test_case(int case_num, const int* nums, size_t len, int target) {
    Indices result = two_sum(nums, len, target);
    printf("Test Case %d: {%zu, %zu}\n", case_num, result.index1, result.index2);
}

int main() {
    // Test case 1
    int nums1[] = {1, 2, 3};
    run_test_case(1, nums1, sizeof(nums1) / sizeof(nums1[0]), 4); // Expected: {0, 2}

    // Test case 2
    int nums2[] = {1234, 5678, 9012};
    run_test_case(2, nums2, sizeof(nums2) / sizeof(nums2[0]), 14690); // Expected: {1, 2}

    // Test case 3
    int nums3[] = {2, 2, 3};
    run_test_case(3, nums3, sizeof(nums3) / sizeof(nums3[0]), 4); // Expected: {0, 1}

    // Test case 4
    int nums4[] = {3, 2, 4};
    run_test_case(4, nums4, sizeof(nums4) / sizeof(nums4[0]), 6); // Expected: {1, 2}

    // Test case 5
    int nums5[] = {3, 3};
    run_test_case(5, nums5, sizeof(nums5) / sizeof(nums5[0]), 6); // Expected: {0, 1}

    return 0;
}