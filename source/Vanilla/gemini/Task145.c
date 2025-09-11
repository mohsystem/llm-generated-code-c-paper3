#include <stdio.h>
#include <stdlib.h>

int* maxSubArray(int* nums, int numsSize, int* returnSize) {
    int maxSoFar = nums[0];
    int currentMax = nums[0];
    int start = 0;
    int end = 0;
    int tempStart = 0;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > currentMax + nums[i]) {
            currentMax = nums[i];
            tempStart = i;
        } else {
            currentMax += nums[i];
        }

        if (currentMax > maxSoFar) {
            maxSoFar = currentMax;
            start = tempStart;
            end = i;
        }
    }

    *returnSize = end - start + 1;
    int* subArray = (int*)malloc(*returnSize * sizeof(int));
    for (int i = 0; i < *returnSize; i++) {
        subArray[i] = nums[start + i];
    }
    return subArray;
}

int main() {
    int test1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int size1;
    int* result1 = maxSubArray(test1, sizeof(test1) / sizeof(test1[0]), &size1);
    for (int i = 0; i < size1; i++) printf("%d ", result1[i]);
    printf("\n"); // Output: 4 -1 2 1
    free(result1);


    int test2[] = {1};
    int size2;
    int* result2 = maxSubArray(test2, sizeof(test2) / sizeof(test2[0]), &size2);
    for (int i = 0; i < size2; i++) printf("%d ", result2[i]);
    printf("\n"); // Output: 1
    free(result2);

    int test3[] = {5, 4, -1, 7, 8};
    int size3;
    int* result3 = maxSubArray(test3, sizeof(test3) / sizeof(test3[0]), &size3);
    for (int i = 0; i < size3; i++) printf("%d ", result3[i]);
    printf("\n"); // Output: 5 4 -1 7 8
    free(result3);

    int test4[] = {-2, -1};
    int size4;
    int* result4 = maxSubArray(test4, sizeof(test4) / sizeof(test4[0]), &size4);
    for (int i = 0; i < size4; i++) printf("%d ", result4[i]);
    printf("\n"); // Output: -1
    free(result4);


    int test5[] = {-1, -2, -3, -4};
    int size5;
    int* result5 = maxSubArray(test5, sizeof(test5) / sizeof(test5[0]), &size5);
    for (int i = 0; i < size5; i++) printf("%d ", result5[i]);
    printf("\n"); // Output: -1
    free(result5);

    return 0;
}