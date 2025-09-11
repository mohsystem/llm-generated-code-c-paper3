#include <stdio.h>
#include <stdlib.h>

void mergeSort(int* nums, int* indices, int* counts, int start, int end) {
    if (start >= end) return;
    int mid = start + (end - start) / 2;
    mergeSort(nums, indices, counts, start, mid);
    mergeSort(nums, indices, counts, mid + 1, end);
    merge(nums, indices, counts, start, mid, end);
}

void merge(int* nums, int* indices, int* counts, int start, int mid, int end) {
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

    int i = 0, j = 0, k = start;
    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            indices[k] = start + i;
            counts[start + i] += j;
            k++;
            i++;
        } else {
            indices[k] = mid + 1 + j;
            k++;
            j++;
        }
    }
    while (i < leftSize) {
        indices[k] = start + i;
        counts[start + i] += j;
        k++;
        i++;
    }
    while (j < rightSize) {
        indices[k] = mid + 1 + j;
        k++;
        j++;
    }

    free(left);
    free(right);
}

int* countSmaller(int* nums, int n) {
    int* counts = (int*)calloc(n, sizeof(int));
    int* indices = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }
    mergeSort(nums, indices, counts, 0, n - 1);
    free(indices);
    return counts;
}

int main() {
    int nums1[] = {5, 2, 6, 1};
    int n1 = sizeof(nums1) / sizeof(nums1[0]);
    int* result1 = countSmaller(nums1, n1);
    for (int i = 0; i < n1; i++) {
        printf("%d ", result1[i]);
    }
    printf("\n"); // [2, 1, 1, 0]
    free(result1);

    int nums2[] = {-1};
    int n2 = sizeof(nums2) / sizeof(nums2[0]);
    int* result2 = countSmaller(nums2, n2);
    for (int i = 0; i < n2; i++) {
        printf("%d ", result2[i]);
    }
    printf("\n"); // [0]
    free(result2);

    int nums3[] = {-1, -1};
    int n3 = sizeof(nums3) / sizeof(nums3[0]);
    int* result3 = countSmaller(nums3, n3);
    for (int i = 0; i < n3; i++) {
        printf("%d ", result3[i]);
    }
    printf("\n"); // [0, 0]
    free(result3);

    int nums4[] = {12, 1, 2, 3, 0, 11, 4};
    int n4 = sizeof(nums4) / sizeof(nums4[0]);
    int* result4 = countSmaller(nums4, n4);
    for (int i = 0; i < n4; i++) {
        printf("%d ", result4[i]);
    }
    printf("\n"); // [6, 1, 1, 1, 0, 1, 0]
    free(result4);

    int nums5[] = {5, 4, 3, 2, 1};
    int n5 = sizeof(nums5) / sizeof(nums5[0]);
    int* result5 = countSmaller(nums5, n5);
    for (int i = 0; i < n5; i++) {
        printf("%d ", result5[i]);
    }
    printf("\n"); // [4, 3, 2, 1, 0]
    free(result5);

    return 0;
}