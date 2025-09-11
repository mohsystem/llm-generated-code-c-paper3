#include <stdio.h>
#include <stdlib.h>

int maxSumSubsequence(int* nums, int n, int k) {
    int dp[n];
    int maxSum = nums[0];
    for (int i = 0; i < n; i++) {
        dp[i] = nums[i];
        for (int j = i - 1; j >= 0 && i - j <= k; j--) {
            dp[i] = dp[i] > dp[j] + nums[i] ? dp[i] : dp[j] + nums[i];
        }
        maxSum = maxSum > dp[i] ? maxSum : dp[i];
    }
    return maxSum;
}

int main() {
    int nums1[] = {10,2,-10,5,20};
    int nums2[] = {-1,-2,-3};
    int nums3[] = {10,-2,-10,-5,20};
    printf("%d\n", maxSumSubsequence(nums1, 5, 2)); // 37
    printf("%d\n", maxSumSubsequence(nums2, 3, 1)); // -1
    printf("%d\n", maxSumSubsequence(nums3, 5, 2)); // 23
    return 0;
}