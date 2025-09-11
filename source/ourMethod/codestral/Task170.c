#include <stdio.h>

int numSubarrayBoundedMax(int* nums, int numsSize, int lower, int upper) {
    int result = 0;
    int j = 0, k = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] >= lower && nums[i] <= upper) {
            k = i + 1;
        } else if (nums[i] > upper) {
            j = k = i + 1;
        }
        result += k - j;
    }
    return result;
}

int main() {
    int nums1[] = {-2,5,-1};
    int nums2[] = {0};
    printf("%d\n", numSubarrayBoundedMax(nums1, 3, -2, 2)); // Output: 3
    printf("%d\n", numSubarrayBoundedMax(nums2, 1, 0, 0)); // Output: 1
    return 0;
}