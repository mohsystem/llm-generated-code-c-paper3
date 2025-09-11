#include<stdio.h>

int xorGame(int* nums, int numsSize) {
    int xor = 0;
    for (int i = 0; i < numsSize; i++) {
        xor ^= nums[i];
    }
    if (xor == 0) {
        return 0;
    }
    return numsSize % 2 == 0 ? 0 : 1;
}

int main() {
    int nums1[] = {1, 1, 2};
    int nums2[] = {0, 1};
    int nums3[] = {1, 2, 3};
    printf("%d\n", xorGame(nums1, 3));  // Output: 0
    printf("%d\n", xorGame(nums2, 2));  // Output: 1
    printf("%d\n", xorGame(nums3, 3));  // Output: 1
    return 0;
}