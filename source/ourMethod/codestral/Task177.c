#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int max_sum_subsequence(int* nums, int numsSize, int k) {
    int dp[numsSize];
    dp[0] = nums[0];
    int max_val = dp[0];
    for (int i = 1; i < numsSize; i++) {
        dp[i] = max(dp[i - 1] + nums[i], nums[i]);
        if (i >= k) {
            dp[i] = max(dp[i], dp[i - k] + nums[i]);
        }
        max_val = max(max_val, dp[i]);
    }
    return max_val;
}

int main() {
    int nums1[] = {10,2,-10,5,20};
    printf("%d\n", max_sum_subsequence(nums1, 5, 2)); // Expected output: 37

    int nums2[] = {-1,-2,-3};
    printf("%d\n", max_sum_subsequence(nums2, 3, 1)); // Expected output: -1

    int nums3[] = {10,-2,-10,-5,20};
    printf("%d\n", max_sum_subsequence(nums3, 5, 2)); // Expected output: 23

    return 0;
}