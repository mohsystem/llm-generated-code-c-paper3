#include <stdio.h>

int maxSubArraySum(const int* nums, int size) {
    int maxSum = nums[0];
    int currentSum = nums[0];
    for (int i = 1; i < size; i++) {
        if (nums[i] > currentSum + nums[i]) {
            currentSum = nums[i];
        } else {
            currentSum += nums[i];
        }
        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
    }
    return maxSum;
}

int main() {
    int nums1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int nums2[] = {1};
    int nums3[] = {5, 4, -1, 7, 8};
    int nums4[] = {-1, -2, -3, -4};
    int nums5[] = {3, -1, 2, -1};

    printf("%d\n", maxSubArraySum(nums1, 9)); // Output: 6
    printf("%d\n", maxSubArraySum(nums2, 1)); // Output: 1
    printf("%d\n", maxSubArraySum(nums3, 5)); // Output: 23
    printf("%d\n", maxSubArraySum(nums4, 4)); // Output: -1
    printf("%d\n", maxSubArraySum(nums5, 4)); // Output: 4

    return 0;
}