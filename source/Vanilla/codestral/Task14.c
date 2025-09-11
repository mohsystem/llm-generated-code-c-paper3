#include <stdio.h>

int findMiddleIndex(int* nums, int numsSize) {
    int totalSum = 0;
    int leftSum = 0;
    for (int i = 0; i < numsSize; i++) {
        totalSum += nums[i];
    }
    for (int i = 0; i < numsSize; i++) {
        if (leftSum == totalSum - leftSum - nums[i]) {
            return i;
        }
        leftSum += nums[i];
    }
    return -1;
}

int main() {
    int arr1[] = {1,2,3,4,3,2,1};
    int arr2[] = {1,100,50,-51,1,1};
    int arr3[] = {20,10,-80,10,10,15,35};
    int arr4[] = {1,2,3};
    int arr5[] = {2,1,-1};
    printf("%d\n", findMiddleIndex(arr1, sizeof(arr1)/sizeof(arr1[0]))); // Output: 3
    printf("%d\n", findMiddleIndex(arr2, sizeof(arr2)/sizeof(arr2[0]))); // Output: 1
    printf("%d\n", findMiddleIndex(arr3, sizeof(arr3)/sizeof(arr3[0]))); // Output: 0
    printf("%d\n", findMiddleIndex(arr4, sizeof(arr4)/sizeof(arr4[0]))); // Output: -1
    printf("%d\n", findMiddleIndex(arr5, sizeof(arr5)/sizeof(arr5[0]))); // Output: 0
    return 0;
}