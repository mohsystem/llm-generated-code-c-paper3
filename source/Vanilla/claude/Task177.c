
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int maxSubsequenceSum(int* nums, int numsSize, int k) {
    int* dp = (int*)malloc(numsSize * sizeof(int));
    dp[0] = nums[0];
    
    for (int i = 1; i < numsSize; i++) {
        dp[i] = nums[i];
        int maxPrev = 0;
        for (int j = max(0, i - k); j < i; j++) {
            maxPrev = max(maxPrev, dp[j]);
        }
        if (maxPrev > 0) {
            dp[i] += maxPrev;
        }
    }
    
    int maxSum = INT_MIN;
    for (int i = 0; i < numsSize; i++) {
        maxSum = max(maxSum, dp[i]);
    }
    
    free(dp);
    return maxSum;
}

int main() {
    // Test case 1
    int nums1[] = {10, 2, -10, 5, 20};
    printf("%d\\n", maxSubsequenceSum(nums1, 5, 2));  // Expected: 37

    // Test case 2
    int nums2[] = {-1, -2, -3};
    printf("%d\\n", maxSubsequenceSum(nums2, 3, 1));  // Expected: -1

    // Test case 3
    int nums3[] = {10, -2, -10, -5, 20};
    printf("%d\\n", maxSubsequenceSum(nums3, 5, 2));  // Expected: 23

    // Test case 4
    int nums4[] = {1, 2, 3, 4, 5};
    printf("%d\\n", maxSubsequenceSum(nums4, 5, 1));  // Expected: 9

    // Test case 5
    int nums5[] = {-5, -4, -3, -2, -1};
    printf("%d\\n", maxSubsequenceSum(nums5, 5, 3));  // Expected: -1

    return 0;
}
