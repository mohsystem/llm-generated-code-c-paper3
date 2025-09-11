#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int* result = (int*)malloc(2 * sizeof(int));
    int* numMap = (int*)calloc(10000, sizeof(int));

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        if (numMap[abs(complement)] != 0) {
            result[0] = numMap[abs(complement)] - 1;
            result[1] = i;
            *returnSize = 2;
            free(numMap);
            return result;
        }
        numMap[abs(nums[i])] = i + 1;
    }

    *returnSize = 0;
    free(numMap);
    return result;
}

int main() {
    int test1[] = {1, 2, 3};
    int returnSize1;
    int* result1 = twoSum(test1, 3, 4, &returnSize1);
    printf("[%d, %d]\n", result1[0], result1[1]);
    free(result1);

    int test2[] = {3, 2, 4};
    int returnSize2;
    int* result2 = twoSum(test2, 3, 6, &returnSize2);
    printf("[%d, %d]\n", result2[0], result2[1]);
    free(result2);

    int test3[] = {1, 3, 5, 7};
    int returnSize3;
    int* result3 = twoSum(test3, 4, 8, &returnSize3);
    printf("[%d, %d]\n", result3[0], result3[1]);
    free(result3);

    int test4[] = {2, 7, 11, 15};
    int returnSize4;
    int* result4 = twoSum(test4, 4, 9, &returnSize4);
    printf("[%d, %d]\n", result4[0], result4[1]);
    free(result4);

    int test5[] = {-3, 4, 3, 90};
    int returnSize5;
    int* result5 = twoSum(test5, 4, 0, &returnSize5);
    printf("[%d, %d]\n", result5[0], result5[1]);
    free(result5);

    return 0;
}