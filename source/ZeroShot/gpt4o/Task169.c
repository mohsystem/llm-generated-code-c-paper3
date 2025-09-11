#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int index;
} Pair;

void merge(Pair* arr, int start, int mid, int end, int* counts) {
    int leftSize = mid - start;
    int rightSize = end - mid;
    Pair* left = (Pair*)malloc(leftSize * sizeof(Pair));
    Pair* right = (Pair*)malloc(rightSize * sizeof(Pair));

    for (int i = 0; i < leftSize; i++)
        left[i] = arr[start + i];
    for (int i = 0; i < rightSize; i++)
        right[i] = arr[mid + i];

    int i = 0, j = 0, k = start, rightCount = 0;
    while (i < leftSize && j < rightSize) {
        if (left[i].value <= right[j].value) {
            counts[left[i].index] += rightCount;
            arr[k++] = left[i++];
        } else {
            rightCount++;
            arr[k++] = right[j++];
        }
    }

    while (i < leftSize) {
        counts[left[i].index] += rightCount;
        arr[k++] = left[i++];
    }

    while (j < rightSize) {
        arr[k++] = right[j++];
    }

    free(left);
    free(right);
}

void mergeSort(Pair* arr, int start, int end, int* counts) {
    if (end - start <= 1) return;
    int mid = (start + end) / 2;
    mergeSort(arr, start, mid, counts);
    mergeSort(arr, mid, end, counts);
    merge(arr, start, mid, end, counts);
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* counts = (int*)calloc(numsSize, sizeof(int));
    Pair* arr = (Pair*)malloc(numsSize * sizeof(Pair));

    for (int i = 0; i < numsSize; i++) {
        arr[i].value = nums[i];
        arr[i].index = i;
    }

    mergeSort(arr, 0, numsSize, counts);
    free(arr);
    return counts;
}

int main() {
    int test1[] = {5, 2, 6, 1};
    int test2[] = {-1};
    int test3[] = {-1, -1};
    int test4[] = {2, 0, 1};
    int test5[] = {7, 6, 5, 4, 3};
    int* tests[] = {test1, test2, test3, test4, test5};
    int sizes[] = {4, 1, 2, 3, 5};
    int numTests = 5;
    int returnSize;

    for (int i = 0; i < numTests; i++) {
        int* result = countSmaller(tests[i], sizes[i], &returnSize);
        for (int j = 0; j < returnSize; j++) {
            printf("%d ", result[j]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}