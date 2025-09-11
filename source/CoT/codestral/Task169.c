#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    int* ans = (int*)malloc(numsSize * sizeof(int));
    int* sorted = (int*)malloc(numsSize * sizeof(int));
    *returnSize = numsSize;
    for (int i = numsSize - 1; i >= 0; i--) {
        int* pos = (int*)bsearch(&nums[i], sorted, numsSize - i - 1, sizeof(int), compare);
        int idx = pos ? (pos - sorted) : 0;
        for (int j = numsSize - i - 1; j > idx; j--) {
            sorted[j] = sorted[j - 1];
        }
        sorted[idx] = nums[i];
        ans[i] = idx;
    }
    free(sorted);
    return ans;
}

int main() {
    int nums1[] = {5, 2, 6, 1};
    int nums2[] = {-1};
    int nums3[] = {-1, -1};
    int returnSize1, returnSize2, returnSize3;
    int* res1 = countSmaller(nums1, 4, &returnSize1);
    int* res2 = countSmaller(nums2, 1, &returnSize2);
    int* res3 = countSmaller(nums3, 2, &returnSize3);
    for (int i = 0; i < returnSize1; i++) printf("%d ", res1[i]);
    printf("\n");
    for (int i = 0; i < returnSize2; i++) printf("%d ", res2[i]);
    printf("\n");
    for (int i = 0; i < returnSize3; i++) printf("%d ", res3[i]);
    printf("\n");
    free(res1);
    free(res2);
    free(res3);
    return 0;
}