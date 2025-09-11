#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;

    // Using a simple approach for C as it does not have built-in hash maps
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                result[0] = i;
                result[1] = j;
                return result;
            }
        }
    }

    free(result);
    *returnSize = 0;
    return NULL;
}

int main() {
    int test1[] = {1, 2, 3};
    int target1 = 4;
    int returnSize1;
    int* result1 = twoSum(test1, 3, target1, &returnSize1);
    printf("[%d, %d]\n", result1[0], result1[1]); // Output: [0, 2]
    free(result1);

    int test2[] = {3, 2, 4};
    int target2 = 6;
    int returnSize2;
    int* result2 = twoSum(test2, 3, target2, &returnSize2);
    printf("[%d, %d]\n", result2[0], result2[1]); // Output: [1, 2]
    free(result2);

    return 0;
}