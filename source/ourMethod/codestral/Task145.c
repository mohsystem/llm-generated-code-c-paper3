#include <stdio.h>
#include <stdlib.h>

int* maxSubArray(int* nums, int numsSize, int* returnSize) {
    int maxSum = nums[0];
    int currentSum = nums[0];
    int start = 0, end = 0, temp = 0;

    for (int i = 1; i < numsSize; i++) {
        if (currentSum < 0) {
            currentSum = nums[i];
            temp = i;
        } else {
            currentSum += nums[i];
        }

        if (currentSum > maxSum) {
            maxSum = currentSum;
            start = temp;
            end = i;
        }
    }

    *returnSize = end - start + 1;
    int* result = malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; i++) {
        result[i] = nums[start + i];
    }
    return result;
}

int main() {
    int testCases[5][9] = {
        {-2, -3, 4, -1, -2, 1, 5, -3, 0},
        {-2, 1, -3, 4, -1, 2, 1, -5, 4},
        {1, 2, 3, 4, -10, 0, 0, 0, 0},
        {-1, -2, -3, -4, -5, 0, 0, 0, 0},
        {1, 2, -5, 6, 7, -10, 1, 2, 3}
    };

    for (int i = 0; i < 5; i++) {
        printf("Array: ");
        for (int j = 0; j < 9; j++) {
            printf("%d ", testCases[i][j]);
        }
        printf("\nMax Subarray: ");
        int returnSize;
        int* result = maxSubArray(testCases[i], 9, &returnSize);
        for (int j = 0; j < returnSize; j++) {
            printf("%d ", result[j]);
        }
        printf("\n\n");
        free(result);
    }

    return 0;
}