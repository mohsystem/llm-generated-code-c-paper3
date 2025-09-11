#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int maxSumWithNoConsecutiveElements(int* nums, int n, int k) {
    int dp[n];
    dp[0] = nums[0];
    int maxSum = dp[0];

    for (int i = 1; i < n; i++) {
        dp[i] = nums[i];
        for (int j = max(0, i - k); j < i; j++) {
            dp[i] = max(dp[i], dp[j] + nums[i]);
        }
        maxSum = max(maxSum, dp[i]);
    }
    return maxSum;
}

int main() {
    int nums1[] = {10, 2, -10, 5, 20};
    int nums2[] = {-1, -2, -3};
    int nums3[] = {10, -2, -10, -5, 20};

    printf("%d\n", maxSumWithNoConsecutiveElements(nums1, 5, 2));  // Output: 37
    printf("%d\n", maxSumWithNoConsecutiveElements(nums2, 3, 1));  // Output: -1
    printf("%d\n", maxSumWithNoConsecutiveElements(nums3, 5, 2));  // Output: 23

    return 0;
}