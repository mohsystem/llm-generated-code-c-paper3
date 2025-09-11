#include <stdio.h>
#include <stdbool.h>

bool xorGame(int nums[], int numsSize) {
    int xor_sum = 0;
    for (int i = 0; i < numsSize; i++) {
        xor_sum ^= nums[i];
    }
    if (xor_sum == 0) {
        return true;
    }
    return numsSize % 2 == 0;
}

int main() {
    int nums1[] = {1, 1, 2};
    printf("%s\n", xorGame(nums1, 3) ? "true" : "false"); // false

    int nums2[] = {0, 1};
    printf("%s\n", xorGame(nums2, 2) ? "true" : "false"); // true

    int nums3[] = {1, 2, 3};
    printf("%s\n", xorGame(nums3, 3) ? "true" : "false"); // true

    int nums4[] = {1, 1};
    printf("%s\n", xorGame(nums4, 2) ? "true" : "false"); // true

    int nums5[] = {1, 2, 0};
    printf("%s\n", xorGame(nums5, 3) ? "true" : "false"); // true


    return 0;
}