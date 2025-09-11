#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int *result = malloc(2 * sizeof(int));
    *returnSize = 2;
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
    return NULL;
}

int main() {
    int returnSize;
    int *result1 = twoSum((int[]){1, 2, 3}, 3, 4, &returnSize);
    printf("[%d, %d]\n", result1[0], result1[1]);  // Output: [0, 2]
    int *result2 = twoSum((int[]){3, 2, 4}, 3, 6, &returnSize);
    printf("[%d, %d]\n", result2[0], result2[1]);  // Output: [1, 2]
    free(result1);
    free(result2);
    return 0;
}