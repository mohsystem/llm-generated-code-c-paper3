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
    int returnSize1;
    int* output1 = countSmaller(nums1, 4, &returnSize1);
    for (int i = 0; i < returnSize1; i++) printf("%d ", output1[i]); // Output: 2 1 1 0
    printf("\n");
    free(output1);

    int nums2[] = {-1};
    int returnSize2;
    int* output2 = countSmaller(nums2, 1, &returnSize2);
    for (int i = 0; i < returnSize2; i++) printf("%d ", output2[i]); // Output: 0
    printf("\n");
    free(output2);

    int nums3[] = {-1, -1};
    int returnSize3;
    int* output3 = countSmaller(nums3, 2, &returnSize3);
    for (int i = 0; i < returnSize3; i++) printf("%d ", output3[i]); // Output: 0 0
    printf("\n");
    free(output3);


    int nums4[] = {1, 2, 3, 4};
    int returnSize4;
    int* output4 = countSmaller(nums4, 4, &returnSize4);
    for (int i = 0; i < returnSize4; i++) printf("%d ", output4[i]); // Output: 0 0 0 0
    printf("\n");
    free(output4);

    int nums5[] = {4, 3, 2, 1};
    int returnSize5;
    int* output5 = countSmaller(nums5, 4, &returnSize5);
    for (int i = 0; i < returnSize5; i++) printf("%d ", output5[i]); // Output: 3 2 1 0
    printf("\n");
    free(output5);
    return 0;
}