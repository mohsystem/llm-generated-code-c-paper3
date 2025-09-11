#include <stdio.h>
#include <stdlib.h>

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    int* result = (int*)malloc(numsSize * sizeof(int));
    *returnSize = numsSize;

    for (int i = 0; i < numsSize; i++) {
        int count = 0;
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[j] < nums[i]) {
                count++;
            }
        }
        result[i] = count;
    }
    return result;
}

int main() {
    int nums1[] = {5, 2, 6, 1};
    int numsSize1 = sizeof(nums1) / sizeof(nums1[0]);
    int returnSize1;
    int* result1 = countSmaller(nums1, numsSize1, &returnSize1);
    for (int i = 0; i < returnSize1; i++) {
        printf("%d ", result1[i]);
    }
    printf("\n"); // Output: 2 1 1 0
    free(result1);

    int nums2[] = {-1};
    int numsSize2 = sizeof(nums2) / sizeof(nums2[0]);
    int returnSize2;
    int* result2 = countSmaller(nums2, numsSize2, &returnSize2);
    for (int i = 0; i < returnSize2; i++) {
        printf("%d ", result2[i]);
    }
    printf("\n"); // Output: 0
    free(result2);

    int nums3[] = {-1, -1};
    int numsSize3 = sizeof(nums3) / sizeof(nums3[0]);
    int returnSize3;
    int* result3 = countSmaller(nums3, numsSize3, &returnSize3);
    for (int i = 0; i < returnSize3; i++) {
        printf("%d ", result3[i]);
    }
    printf("\n"); // Output: 0 0
    free(result3);

    int nums4[] = {1, 2, 3, 4};
    int numsSize4 = sizeof(nums4) / sizeof(nums4[0]);
    int returnSize4;
    int* result4 = countSmaller(nums4, numsSize4, &returnSize4);
    for (int i = 0; i < returnSize4; i++) {
        printf("%d ", result4[i]);
    }
    printf("\n"); // Output: 0 0 0 0
    free(result4);

    int nums5[] = {4, 3, 2, 1};
    int numsSize5 = sizeof(nums5) / sizeof(nums5[0]);
    int returnSize5;
    int* result5 = countSmaller(nums5, numsSize5, &returnSize5);
    for (int i = 0; i < returnSize5; i++) {
        printf("%d ", result5[i]);
    }
    printf("\n"); // Output: 3 2 1 0
    free(result5);

    return 0;
}