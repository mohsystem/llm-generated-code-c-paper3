#include <stdio.h>
#include <stdlib.h>

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    int* result = (int*)malloc(numsSize * sizeof(int));
    int* sorted = (int*)malloc(numsSize * sizeof(int));
    int sortedSize = 0;
    
    for (int i = numsSize - 1; i >= 0; i--) {
        int left = 0, right = sortedSize;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (sorted[mid] >= nums[i]) right = mid;
            else left = mid + 1;
        }
        
        for (int j = sortedSize; j > left; j--) {
            sorted[j] = sorted[j - 1];
        }
        sorted[left] = nums[i];
        result[i] = left;
        sortedSize++;
    }
    
    *returnSize = numsSize;
    free(sorted);
    return result;
}

int main() {
    int testCases[5][7] = {
        {5, 2, 6, 1}, 
        {-1}, 
        {-1, -1}, 
        {2, 0, 1}, 
        {7, 6, 5, 4, 3, 2, 1}
    };
    int testSizes[5] = {4, 1, 2, 3, 7};
    
    for (int i = 0; i < 5; i++) {
        int returnSize;
        int* result = countSmaller(testCases[i], testSizes[i], &returnSize);
        for (int j = 0; j < returnSize; j++) {
            printf("%d ", result[j]);
        }
        printf("\n");
        free(result);
    }
    return 0;
}