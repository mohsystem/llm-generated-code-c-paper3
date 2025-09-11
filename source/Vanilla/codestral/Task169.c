#include <stdlib.h>
#include <stdio.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* sorted = malloc(numsSize * sizeof(int));
    int* result = malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        sorted[i] = nums[i];
    }
    qsort(sorted, numsSize, sizeof(int), compare);
    for (int i = 0; i < numsSize; i++) {
        int* pos = (int*)bsearch(&nums[i], sorted, numsSize, sizeof(int), compare);
        result[i] = pos - sorted;
        for (int j = result[i]; j < numsSize - 1; j++) {
            sorted[j] = sorted[j + 1];
        }
        numsSize--;
    }
    free(sorted);
    return result;
}

int main() {
    int returnSize;
    int* result = countSmaller((int[]){5,2,6,1}, 4, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    result = countSmaller((int[]){-1}, 1, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    result = countSmaller((int[]){-1,-1}, 2, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    return 0;
}