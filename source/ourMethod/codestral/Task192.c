#include <stdio.h>
#include <stdbool.h>

bool canWinNim(int* nums, int numsSize) {
    int xor = 0;
    for (int i = 0; i < numsSize; i++) {
        xor ^= nums[i];
    }
    return xor != 0;
}

int main() {
    int nums1[] = {1, 1, 2};
    printf("%d\n", canWinNim(nums1, sizeof(nums1) / sizeof(nums1[0])));  // 0 (false)

    int nums2[] = {0, 1};
    printf("%d\n", canWinNim(nums2, sizeof(nums2) / sizeof(nums2[0])));  // 1 (true)

    int nums3[] = {1, 2, 3};
    printf("%d\n", canWinNim(nums3, sizeof(nums3) / sizeof(nums3[0])));  // 1 (true)

    return 0;
}