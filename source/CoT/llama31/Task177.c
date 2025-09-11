#include <stdio.h>
#include <limits.h>

int maximumSum(int nums[], int n, int k) {
    int dp[n];
    int maxSum = INT_MIN;

    for (int i = 0; i < n; i++) {
        dp[i] = nums[i];
        maxSum = (maxSum > nums[i]) ? maxSum : nums[i];
        for (int j = 1; j <= k && i - j >= 0; j++) {
            dp[i] = (dp[i] > dp[i - j] + nums[i]) ? dp[i] : dp[i - j] + nums[i];
            maxSum = (maxSum > dp[i]) ? maxSum : dp[i];
        }
    }
    return maxSum;
}

int main() {
    int nums1[] = {10, 2, -10, 5, 20};
    int k1 = 2;
    printf("Output: %d\n", maximumSum(nums1, 5, k1)); // Output: 37

    int nums2[] = {-1, -2, -3};
    int k2 = 1;
    printf("Output: %d\n", maximumSum(nums2, 3, k2)); // Output: -1

    int nums3[] = {10, -2, -10, -5, 20};
    int k3 = 2;
    printf("Output: %d\n", maximumSum(nums3, 5, k3)); // Output: 23

    int nums4[] = {1, 2, 3, 4, 5};
    int k4 = 3;
    printf("Output: %d\n", maximumSum(nums4, 5, k4)); // Output: 15

    int nums5[] = {-10, -20, -30};
    int k5 = 2;
    printf("Output: %d\n", maximumSum(nums5, 3, k5)); // Output: -10

    return 0;
}