#include <stdio.h>
#include <stdbool.h>

bool xorGame(int* nums, int numsSize) {
    int xor = 0;
    for (int i = 0; i < numsSize; i++) {
        xor ^= nums[i];
    }
    return xor == 0 || numsSize % 2 == 0;
}

int main() {
    int nums1[] = {1, 1, 2};
    printf("%d\n", xorGame(nums1, 3));  // 0 (false)

    int nums2[] = {0, 1};
    printf("%d\n", xorGame(nums2, 2));  // 1 (true)

    int nums3[] = {1, 2, 3};
    printf("%d\n", xorGame(nums3, 3));  // 1 (true)

    return 0;
}