#include <stdio.h>
#include <stdbool.h>

bool xorGame(int* nums, int numsSize) {
    int xor = 0;
    for (int i = 0; i < numsSize; i++) {
        xor ^= nums[i];
    }
    if (xor == 0) {
        return false;
    }
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        if ((xor ^ nums[i]) < nums[i]) {
            count++;
        }
    }
    return count % 2 == 1;
}

int main() {
    int nums1[] = {1, 1, 2};
    printf("%d\n", xorGame(nums1, 3)); // false
    int nums2[] = {0, 1};
    printf("%d\n", xorGame(nums2, 2)); // true
    int nums3[] = {1, 2, 3};
    printf("%d\n", xorGame(nums3, 3)); // true
    return 0;
}