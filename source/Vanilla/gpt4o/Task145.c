#include <stdio.h>

int maxSubArray(int* nums, int numsSize) {
    int maxSoFar = nums[0];
    int maxEndingHere = nums[0];
    
    for (int i = 1; i < numsSize; i++) {
        maxEndingHere = nums[i] > (maxEndingHere + nums[i]) ? nums[i] : (maxEndingHere + nums[i]);
        maxSoFar = maxSoFar > maxEndingHere ? maxSoFar : maxEndingHere;
    }
    
    return maxSoFar;
}

void runTestCases() {
    int nums1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int nums2[] = {1};
    int nums3[] = {5, 4, -1, 7, 8};
    int nums4[] = {-1, -2, -3, -4};
    int nums5[] = {1, 2, 3, 4, 5};
    
    printf("%d\n", maxSubArray(nums1, 9)); // 6
    printf("%d\n", maxSubArray(nums2, 1)); // 1
    printf("%d\n", maxSubArray(nums3, 5)); // 23
    printf("%d\n", maxSubArray(nums4, 4)); // -1
    printf("%d\n", maxSubArray(nums5, 5)); // 15
}

int main() {
    runTestCases();
    return 0;
}