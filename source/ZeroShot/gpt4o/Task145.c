#include <stdio.h>

int maxSubArray(int* nums, int numsSize) {
    if (nums == NULL || numsSize == 0) return 0;
    int maxSum = nums[0];
    int currentSum = nums[0];
    for (int i = 1; i < numsSize; i++) {
        currentSum = nums[i] > (currentSum + nums[i]) ? nums[i] : (currentSum + nums[i]);
        maxSum = maxSum > currentSum ? maxSum : currentSum;
    }
    return maxSum;
}

int main() {
    int arr1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    printf("%d\n", maxSubArray(arr1, 9)); // 6

    int arr2[] = {1};
    printf("%d\n", maxSubArray(arr2, 1)); // 1

    int arr3[] = {5, 4, -1, 7, 8};
    printf("%d\n", maxSubArray(arr3, 5)); // 23

    int arr4[] = {-1, -2, -3, -4};
    printf("%d\n", maxSubArray(arr4, 4)); // -1

    int arr5[] = {2, -1, 2, 3, 4, -5};
    printf("%d\n", maxSubArray(arr5, 6)); // 10

    return 0;
}