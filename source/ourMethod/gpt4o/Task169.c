#include <stdio.h>
#include <stdlib.h>

void merge(int* nums, int* indices, int* counts, int left, int mid, int right) {
    int* temp = (int*)malloc((right - left) * sizeof(int));
    int i = left, j = mid, k = 0;
    while (i < mid && j < right) {
        if (nums[indices[i]] <= nums[indices[j]]) {
            counts[indices[i]] += j - mid;
            temp[k++] = indices[i++];
        } else {
            temp[k++] = indices[j++];
        }
    }
    while (i < mid) {
        counts[indices[i]] += j - mid;
        temp[k++] = indices[i++];
    }
    while (j < right) {
        temp[k++] = indices[j++];
    }
    for (i = left, k = 0; i < right; i++, k++) {
        indices[i] = temp[k];
    }
    free(temp);
}

void mergeSort(int* nums, int* indices, int* counts, int left, int right) {
    if (right - left <= 1) return;
    int mid = (left + right) / 2;
    mergeSort(nums, indices, counts, left, mid);
    mergeSort(nums, indices, counts, mid, right);
    merge(nums, indices, counts, left, mid, right);
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    int* counts = (int*)calloc(numsSize, sizeof(int));
    int* indices = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) indices[i] = i;
    mergeSort(nums, indices, counts, 0, numsSize);
    free(indices);
    *returnSize = numsSize;
    return counts;
}

int main() {
    int nums1[] = {5, 2, 6, 1};
    int nums2[] = {-1};
    int nums3[] = {-1, -1};
    int nums4[] = {2, 0, 1};
    int nums5[] = {4, 3, 2, 1};
    int returnSize;
    int* results[5];
    int numsSize1 = sizeof(nums1) / sizeof(nums1[0]);
    int numsSize2 = sizeof(nums2) / sizeof(nums2[0]);
    int numsSize3 = sizeof(nums3) / sizeof(nums3[0]);
    int numsSize4 = sizeof(nums4) / sizeof(nums4[0]);
    int numsSize5 = sizeof(nums5) / sizeof(nums5[0]);
    results[0] = countSmaller(nums1, numsSize1, &returnSize);
    results[1] = countSmaller(nums2, numsSize2, &returnSize);
    results[2] = countSmaller(nums3, numsSize3, &returnSize);
    results[3] = countSmaller(nums4, numsSize4, &returnSize);
    results[4] = countSmaller(nums5, numsSize5, &returnSize);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < returnSize; j++) {
            printf("%d ", results[i][j]);
        }
        printf("\n");
        free(results[i]);
    }
    return 0;
}