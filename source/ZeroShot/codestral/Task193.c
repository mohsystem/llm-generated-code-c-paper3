#include <stdio.h>
#include <stdbool.h>

bool xorGame(int* nums, int numsSize) {
    int xor = 0;
    for (int i = 0; i < numsSize; i++) {
        xor ^= nums[i];
    }
    return xor != 0 && numsSize % 2 == 1;
}

int main() {
    int nums1[] = {1, 1, 2};
    int nums2[] = {0, 1};
    int nums3[] = {1, 2, 3};
    printf("%s\n", xorGame(nums1, 3) ? "true" : "false");  // false
    printf("%s\n", xorGame(nums2, 2) ? "true" : "false");  // true
    printf("%s\n", xorGame(nums3, 3) ? "true" : "false");  // true
    return 0;
}