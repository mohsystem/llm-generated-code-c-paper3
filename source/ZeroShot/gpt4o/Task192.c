#include <stdio.h>
#include <stdbool.h>

bool xorGame(int* nums, int numsSize) {
    int xorSum = 0;
    for (int i = 0; i < numsSize; i++) {
        xorSum ^= nums[i];
    }
    return xorSum == 0 || numsSize % 2 == 0;
}

int main() {
    int nums1[] = {1, 1, 2};
    int nums2[] = {0, 1};
    int nums3[] = {1, 2, 3};
    int nums4[] = {4, 1, 5, 7};
    int nums5[] = {7, 7, 7, 7};
    printf("%s\n", xorGame(nums1, 3) ? "true" : "false"); // false
    printf("%s\n", xorGame(nums2, 2) ? "true" : "false"); // true
    printf("%s\n", xorGame(nums3, 3) ? "true" : "false"); // true
    printf("%s\n", xorGame(nums4, 4) ? "true" : "false"); // true
    printf("%s\n", xorGame(nums5, 4) ? "true" : "false"); // false
    return 0;
}