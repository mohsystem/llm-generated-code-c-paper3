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
    int nums2[] = {0, 1};
    int nums3[] = {1, 2, 3};
    int nums4[] = {5, 5, 5};
    int nums5[] = {4, 1, 7, 3};
    
    printf("%d\n", xorGame(nums1, 3)); // false
    printf("%d\n", xorGame(nums2, 2)); // true
    printf("%d\n", xorGame(nums3, 3)); // true
    printf("%d\n", xorGame(nums4, 3)); // false
    printf("%d\n", xorGame(nums5, 4)); // true
    
    return 0;
}