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
            counts[indices[k]] += j;
            i++;
        } else {
            indices[k] = mid + 1 + j;
            j++;
        }
        k++;
    }

    while (i < leftSize) {
        indices[k] = start + i;
        counts[indices[k]] += j;
        i++;
        k++;
    }

    while (j < rightSize) {
        indices[k] = mid + 1 + j;
        j++;
        k++;
    }

    for (int l = 0; l < leftSize; l++) {
        nums[start + l] = left[l];
    }
    for (int l = 0; l < rightSize; l++) {
        nums[mid + 1 + l] = right[l];
    }

    free(left);
    free(right);
}

int* countSmallerElements(int* nums, int n) {
    int* counts = (int*)malloc(n * sizeof(int));
    int* indices = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        indices[i] = i;
        counts[i] = 0;
    }

    mergeSort(nums, indices, counts, 0, n - 1);
    free(indices);
    return counts;
}

int main() {
    int testCases[][4] = {
        {5, 2, 6, 1},
        {-1},
        {-1, -1}
    };

    for (int i = 0; i < 3; ++i) {
        int len = sizeof(testCases[i]) / sizeof(testCases[i][0]);
        int* nums = (int*)malloc(len * sizeof(int));
        for (int j = 0; j < len; ++j) {
            nums[j] = testCases[i][j];
        }
        int* counts = countSmallerElements(nums, len);
        for (int j = 0; j < len; ++j) {
            printf("%d ", counts[j]);
        }
        printf("\n");
        free(nums);
        free(counts);
    }

    return 0;
}