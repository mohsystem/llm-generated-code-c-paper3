#include <stdio.h>

int reversePairs(int nums[], int numsSize) {
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] > 2LL * nums[j]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int nums1[] = {1, 3, 2, 3, 1};
    int nums2[] = {2, 4, 3, 5, 1};
    int nums3[] = {1};
    int nums4[] = {1, 2, 3, 4, 5};
    int nums5[] = {5, 4, 3, 2, 1};

    printf("%d\n", reversePairs(nums1, 5)); // Output: 2
    printf("%d\n", reversePairs(nums2, 5)); // Output: 3
    printf("%d\n", reversePairs(nums3, 1)); // Output: 0
    printf("%d\n", reversePairs(nums4, 5)); // Output: 0
    printf("%d\n", reversePairs(nums5, 5)); // Output: 10

    return 0;
}