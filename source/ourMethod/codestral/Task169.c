#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int* smallerNumbersThanCurrent(int* nums, int numsSize, int* returnSize) {
    int* counts = (int*)malloc(numsSize * sizeof(int));
    int* sortedNums = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        sortedNums[i] = nums[i];
    }
    qsort(sortedNums, numsSize, sizeof(int), cmp);
    for (int i = 0; i < numsSize; i++) {
        int j = 0;
        while (j < numsSize && sortedNums[j] < nums[i]) {
            j++;
        }
        counts[i] = j;
    }
    *returnSize = numsSize;
    free(sortedNums);
    return counts;
}

int main() {
    int nums1[] = {5, 2, 6, 1};
    int returnSize1;
    int* result1 = smallerNumbersThanCurrent(nums1, 4, &returnSize1);
    for (int i = 0; i < returnSize1; i++) {
        printf("%d ", result1[i]);
    }
    printf("\n");
    free(result1);

    int nums2[] = {-1};
    int returnSize2;
    int* result2 = smallerNumbersThanCurrent(nums2, 1, &returnSize2);
    for (int i = 0; i < returnSize2; i++) {
        printf("%d ", result2[i]);
    }
    printf("\n");
    free(result2);

    int nums3[] = {-1, -1};
    int returnSize3;
    int* result3 = smallerNumbersThanCurrent(nums3, 2, &returnSize3);
    for (int i = 0; i < returnSize3; i++) {
        printf("%d ", result3[i]);
    }
    printf("\n");
    free(result3);

    return 0;
}