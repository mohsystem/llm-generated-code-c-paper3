#include <stdio.h>

int rangeSumCount(int* nums, int numsSize, int lower, int upper) {
    int count = 0;
    int prefixSum[numsSize + 1];
    prefixSum[0] = 0;

    for (int i = 0; i < numsSize; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    for (int i = 0; i < numsSize; i++) {
        for (int j = i; j < numsSize; j++) {
            int sum = prefixSum[j + 1] - prefixSum[i];
            if (sum >= lower && sum <= upper) {
                count++;
            }
        }
    }

    return count;
}

int main() {
    int nums1[] = {-2, 5, -1};
    printf("%d\n", rangeSumCount(nums1, 3, -2, 2)); // Output: 3

    int nums2[] = {0};
    printf("%d\n", rangeSumCount(nums2, 1, 0, 0)); // Output: 1

    return 0;
}