#include <stdio.h>

// Function to find the maximum sum of contiguous subarray
int maxSubArray(int* nums, int numsSize) {
    int maxSoFar = nums[0];
    int maxEndingHere = nums[0];

    for (int i = 1; i < numsSize; i++) {
        if (maxEndingHere + nums[i] > nums[i]) {
            maxEndingHere += nums[i];
        } else {
            maxEndingHere = nums[i];
        }
        if (maxSoFar < maxEndingHere) {
            maxSoFar = maxEndingHere;
        }
    }

    return maxSoFar;
}

int main() {
    // Test cases
    int arr1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int arr2[] = {1};
    int arr3[] = {5, 4, -1, 7, 8};
    int arr4[] = {-1, -2, -3, -4};
    int arr5[] = {-1, 2, 3, -4, 5};

    printf("%d\n", maxSubArray(arr1, 9)); // 6
    printf("%d\n", maxSubArray(arr2, 1)); // 1
    printf("%d\n", maxSubArray(arr3, 5)); // 23
    printf("%d\n", maxSubArray(arr4, 4)); // -1
    printf("%d\n", maxSubArray(arr5, 5)); // 6

    return 0;
}