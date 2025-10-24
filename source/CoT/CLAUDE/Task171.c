
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

// Security: All pointers validated, memory bounds checked, proper cleanup
// Uses merge sort to count reverse pairs efficiently

// Helper function to merge and count reverse pairs
// Security: Validates all array bounds and pointer validity before access
int mergeAndCount(int* nums, int left, int mid, int right, int* temp, int numsSize) {
    // Security: Validate input parameters
    if (nums == NULL || temp == NULL || left < 0 || right >= numsSize || left > mid || mid >= right) {
        return 0;
    }
    
    int count = 0;
    int j = mid + 1;
    
    // Count reverse pairs where i is in left half and j is in right half
    for (int i = left; i <= mid; i++) {
        // Security: Bounds check before array access
        if (i >= numsSize) break;
        
        // Security: Prevent integer overflow when computing 2 * nums[j]
        while (j <= right && j < numsSize) {
            // Use long long to prevent overflow
            long long doubled = 2LL * (long long)nums[j];
            if ((long long)nums[i] > doubled) {
                j++;
            } else {
                break;
            }
        }
        count += (j - (mid + 1));
    }
    
    // Merge the two sorted halves
    int i = left;
    j = mid + 1;
    int k = left;
    
    // Security: Validate bounds during merge
    while (i <= mid && j <= right && i < numsSize && j < numsSize && k < numsSize) {
        if (nums[i] <= nums[j]) {
            temp[k++] = nums[i++];
        } else {
            temp[k++] = nums[j++];
        }
    }
    
    // Copy remaining elements with bounds checking
    while (i <= mid && i < numsSize && k < numsSize) {
        temp[k++] = nums[i++];
    }
    while (j <= right && j < numsSize && k < numsSize) {
        temp[k++] = nums[j++];
    }
    
    // Copy back to original array with bounds validation
    for (int idx = left; idx <= right && idx < numsSize; idx++) {
        nums[idx] = temp[idx];
    }
    
    return count;
}

// Recursive merge sort with pair counting
// Security: Input validation and bounds checking throughout
int mergeSortAndCount(int* nums, int left, int right, int* temp, int numsSize) {
    // Security: Validate input parameters
    if (nums == NULL || temp == NULL || left < 0 || right >= numsSize || left >= right) {
        return 0;
    }
    
    // Security: Prevent integer overflow in mid calculation
    int mid = left + (right - left) / 2;
    int count = 0;
    
    // Recursively count in left and right halves
    count += mergeSortAndCount(nums, left, mid, temp, numsSize);
    count += mergeSortAndCount(nums, mid + 1, right, temp, numsSize);
    
    // Count reverse pairs across the two halves
    count += mergeAndCount(nums, left, mid, right, temp, numsSize);
    
    return count;
}

// Main function to count reverse pairs
// Security: Full input validation and safe memory management
int reversePairs(int* nums, int numsSize) {
    // Security: Validate input pointer and size constraints
    if (nums == NULL || numsSize <= 0 || numsSize > 50000) {
        return 0;
    }
    
    // Security: Allocate temporary array with size validation
    // Check for integer overflow in allocation size
    if (numsSize > SIZE_MAX / sizeof(int)) {
        return 0;
    }
    
    int* temp = (int*)calloc(numsSize, sizeof(int));
    // Security: Check if memory allocation succeeded
    if (temp == NULL) {
        return 0;
    }
    
    int result = mergeSortAndCount(nums, 0, numsSize - 1, temp, numsSize);
    
    // Security: Free allocated memory
    free(temp);
    temp = NULL;
    
    return result;
}

int main() {
    // Test case 1
    int test1[] = {1, 3, 2, 3, 1};
    int size1 = sizeof(test1) / sizeof(test1[0]);
    printf("Test 1: %d (Expected: 2)\\n", reversePairs(test1, size1));
    
    // Test case 2
    int test2[] = {2, 4, 3, 5, 1};
    int size2 = sizeof(test2) / sizeof(test2[0]);
    printf("Test 2: %d (Expected: 3)\\n", reversePairs(test2, size2));
    
    // Test case 3 - single element
    int test3[] = {5};
    int size3 = sizeof(test3) / sizeof(test3[0]);
    printf("Test 3: %d (Expected: 0)\\n", reversePairs(test3, size3));
    
    // Test case 4 - negative numbers
    int test4[] = {-5, -2, -1, -3, -4};
    int size4 = sizeof(test4) / sizeof(test4[0]);
    printf("Test 4: %d (Expected: 0)\\n", reversePairs(test4, size4));
    
    // Test case 5 - large numbers near INT_MAX
    int test5[] = {2147483647, 2147483647, 2147483647, 2147483647, 0};
    int size5 = sizeof(test5) / sizeof(test5[0]);
    printf("Test 5: %d (Expected: 4)\\n", reversePairs(test5, size5));
    
    return 0;
}
