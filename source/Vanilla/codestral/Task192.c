#include <stdio.h>
#include <stdbool.h>

bool canWinNim(int* nums, int numsSize) {
    int xor_val = 0;
    for (int i = 0; i < numsSize; i++) {
        xor_val ^= nums[i];
    }
    return xor_val != 0 && numsSize % 2 != 0;
}

int main() {
    int nums1[] = {1, 1, 2};
    printf("%s\n", canWinNim(nums1, 3) ? "true" : "false"); // false

    int nums2[] = {0, 1};
    printf("%s\n", canWinNim(nums2, 2) ? "true" : "false"); // true

    int nums3[] = {1, 2, 3};
    printf("%s\n", canWinNim(nums3, 3) ? "true" : "false"); // true

    int nums4[] = {4, 8, 16};
    printf("%s\n", canWinNim(nums4, 3) ? "true" : "false"); // false

    int nums5[] = {5, 1, 7};
    printf("%s\n", canWinNim(nums5, 3) ? "true" : "false"); // true

    return 0;
}