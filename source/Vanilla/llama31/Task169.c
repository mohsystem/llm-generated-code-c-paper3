#include <stdio.h>
#include <stdlib.h>

void mergeSort(int* nums, int* indices, int* smallerArr, int start, int end) {
    if (start >= end) return;
    int mid = start + (end - start) / 2;
    mergeSort(nums, indices, smallerArr, start, mid);
    mergeSort(nums, indices, smallerArr, mid + 1, end);
    merge(nums, indices, smallerArr, start, mid, end);
}

void merge(int* nums, int* indices, int* smallerArr, int start, int mid, int end) {
    int leftSize = mid - start + 1;
    int rightSize = end - mid;
    int* left = (int*)malloc(leftSize * sizeof(int));
    int* right = (int*)malloc(rightSize * sizeof(int));
    for (int i = 0; i < leftSize; i++) {
        left[i] = nums[start + i];
    }
    for (int i = 0; i < rightSize; i++) {
        right[i] = nums[mid + 1 + i];
    }
    int l = 0, r = 0, k = start;
    while (l < leftSize && r < rightSize) {
        if (left[l] <= right[r]) {
            nums[k] = left[l];
            smallerArr[indices[start + l]] += r;
            l++;
        } else {
            nums[k] = right[r];
            r++;
        }
        k++;
    }
    while (l < leftSize) {
        nums[k] = left[l];
        smallerArr[indices[start + l]] += r;
        l++;
        k++;
    }
    while (r < rightSize) {
        nums[k] = right[r];
        r++;
        k++;
    }
    free(left);
    free(right);
}

int* countSmaller(int* nums, int n) {
    int* smallerArr = (int*)malloc(n * sizeof(int));
    int* indices = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }
    mergeSort(nums, indices, smallerArr, 0, n - 1);
    free(indices);
    return smallerArr;
}

int main() {
    int nums1[] = {5, 2, 6, 1};
    int* result1 = countSmaller(nums1, 4);
    for (int i = 0; i < 4; i++) printf("%d ", result1[i]); printf("\n"); // [2, 1, 1, 0]
    free(result1);

    int nums2[] = {-1};
    int* result2 = countSmaller(nums2, 1);
    for (int i = 0; i < 1; i++) printf("%d ", result2[i]); printf("\n"); // [0]
    free(result2);

    int nums3[] = {-1, -1};
    int* result3 = countSmaller(nums3, 2);
    for (int i = 0; i < 2; i++) printf("%d ", result3[i]); printf("\n"); // [0, 0]
    free(result3);

    int nums4[] = {3, 2, 2, 1, 0};
    int* result4 = countSmaller(nums4, 5);
    for (int i = 0; i < 5; i++) printf("%d ", result4[i]); printf("\n"); // [3, 2, 1, 0, 0]
    free(result4);

    int nums5[] = {7, 1, 5, 2, 10};
    int* result5 = countSmaller(nums5, 5);
    for (int i = 0; i < 5; i++) printf("%d ", result5[i]); printf("\n"); // [3, 0, 0, 2, 0]
    free(result5);

    return 0;
}