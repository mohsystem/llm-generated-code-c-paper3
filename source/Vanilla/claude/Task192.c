
#include <stdio.h>
#include <stdbool.h>

bool xorGame(int* nums, int numsSize) {
    if (numsSize % 2 == 0) return true;
    
    int xor_sum = 0;
    for (int i = 0; i < numsSize; i++) {
        xor_sum ^= nums[i];
    }
    return xor_sum == 0;
}

int main() {
    // Test case 1
    int nums1[] = {1,1,2};
    printf("%s\\n", xorGame(nums1, 3) ? "true" : "false");  // false
    
    // Test case 2
    int nums2[] = {0,1};
    printf("%s\\n", xorGame(nums2, 2) ? "true" : "false");  // true
    
    // Test case 3
    int nums3[] = {1,2,3};
    printf("%s\\n", xorGame(nums3, 3) ? "true" : "false");  // true
    
    // Test case 4
    int nums4[] = {1,2,3,4};
    printf("%s\\n", xorGame(nums4, 4) ? "true" : "false");  // true
    
    // Test case 5
    int nums5[] = {1,1,1};
    printf("%s\\n", xorGame(nums5, 3) ? "true" : "false");  // false
    
    return 0;
}
