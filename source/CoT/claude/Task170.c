
#include <stdio.h>
#include <stdlib.h>

int countRangeSums(int* nums, int numsSize, int lower, int upper) {
    if (nums == NULL || numsSize == 0) {
        return 0;
    }
    
    int count = 0;
    long long* sums = (long long*)calloc(numsSize + 1, sizeof(long long));
    
    // Calculate prefix sums
    for (int i = 0; i < numsSize; i++) {
        sums[i + 1] = sums[i] + nums[i];
    }
    
    // Check all possible ranges
    for (int i = 0; i < numsSize + 1; i++) {
        for (int j = i + 1; j < numsSize + 1; j++) {
            long long sum = sums[j] - sums[i];
            if (sum >= lower && sum <= upper) {
                count++;
            }
        }
    }
    
    free(sums);
    return count;
}

int main() {
    // Test case 1
    int nums1[] = {-2, 5, -1};
    printf("%d\\n", countRangeSums(nums1, 3, -2, 2));  // Expected: 3
    
    // Test case 2
    int nums2[] = {0};
    printf("%d\\n", countRangeSums(nums2, 1, 0, 0));  // Expected: 1
    
    // Test case 3
    int nums3[] = {1, 2, 3};
    printf("%d\\n", countRangeSums(nums3, 3, 3, 5));  // Expected: 2
    
    // Test case 4
    int nums4[] = {-1, -1, -1};
    printf("%d\\n", countRangeSums(nums4, 3, -2, 0));  // Expected: 4
    
    // Test case 5
    int nums5[] = {1, -1, 1, -1};
    printf("%d\\n", countRangeSums(nums5, 4, -1, 1));  // Expected: 8
    
    return 0;
}
