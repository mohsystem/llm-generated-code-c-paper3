#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int constrainedSubsetSum(int* nums, int numsSize, int k) {
    int* dp = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        dp[i] = INT_MIN;
    }

    for (int i = 0; i < numsSize; i++) {
        int maxSum = 0;
        for (int j = (i - k > 0 ? i-k : 0); j < i; j++) {
            maxSum = (maxSum > dp[j] ? maxSum : dp[j]);
        }
        dp[i] = (nums[i] > nums[i] + maxSum ? nums[i] : nums[i] + maxSum);
    }

    int maxSubsequenceSum = INT_MIN;
    for (int i = 0; i < numsSize; i++) {
        maxSubsequenceSum = (maxSubsequenceSum > dp[i] ? maxSubsequenceSum : dp[i]);
    }

    free(dp);
    return maxSubsequenceSum;
}

int main() {
    int nums1[] = {10, 2, -10, 5, 20};
    int k1 = 2;
    printf("%d\n", constrainedSubsetSum(nums1, 5, k1)); // Output: 37

    int nums2[] = {-1, -2, -3};
    int k2 = 1;
    printf("%d\n", constrainedSubsetSum(nums2, 3, k2)); // Output: -1

    int nums3[] = {10, -2, -10, -5, 20};
    int k3 = 2;
    printf("%d\n", constrainedSubsetSum(nums3, 5, k3)); // Output: 23

    int nums4[] = {1};
    int k4 = 1;
    printf("%d\n", constrainedSubsetSum(nums4, 1, k4)); // Output: 1

    int nums5[] = {-1, -2, -3, -4, -5};
    int k5 = 2;
    printf("%d\n", constrainedSubsetSum(nums5, 5, k5)); // Output: -1
    return 0;
}