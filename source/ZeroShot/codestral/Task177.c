#include<stdio.h>
#include<stdlib.h>

int maxSubsequence(int* nums, int numsSize, int k) {
    int dp[numsSize];
    for (int i = 0; i < numsSize; i++) {
        dp[i] = nums[i];
    }
    int maxVal = dp[0];
    for (int i = 1; i < numsSize; i++) {
        for (int j = (i - k > 0) ? i - k : 0; j < i; j++) {
            if (dp[j] + nums[i] > dp[i]) {
                dp[i] = dp[j] + nums[i];
            }
        }
        maxVal = (maxVal > dp[i]) ? maxVal : dp[i];
    }
    return maxVal;
}

int main() {
    int arr1[] = {10,2,-10,5,20};
    int arr2[] = {-1,-2,-3};
    int arr3[] = {10,-2,-10,-5,20};
    printf("%d\n", maxSubsequence(arr1, 5, 2));
    printf("%d\n", maxSubsequence(arr2, 3, 1));
    printf("%d\n", maxSubsequence(arr3, 5, 2));
    return 0;
}