#include <stdio.h>
#include <stdlib.h>

int* removeSmallest(const int* numbers, int size, int* returnSize) {
    if (size == 0) {
        *returnSize = 0;
        return NULL;
    }
    int minIndex = 0;
    for (int i = 1; i < size; i++) {
        if (numbers[i] < numbers[minIndex]) {
            minIndex = i;
        }
    }
    int* result = (int*)malloc((size - 1) * sizeof(int));
    int j = 0;
    for (int i = 0; i < size; i++) {
        if (i != minIndex) {
            result[j++] = numbers[i];
        }
    }
    *returnSize = size - 1;
    return result;
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int returnSize;
    int nums1[] = {1, 2, 3, 4, 5};
    int* res1 = removeSmallest(nums1, 5, &returnSize);
    printArray(res1, returnSize);
    free(res1);

    int nums2[] = {5, 3, 2, 1, 4};
    int* res2 = removeSmallest(nums2, 5, &returnSize);
    printArray(res2, returnSize);
    free(res2);

    int nums3[] = {2, 2, 1, 2, 1};
    int* res3 = removeSmallest(nums3, 5, &returnSize);
    printArray(res3, returnSize);
    free(res3);

    int nums4[] = {10};
    int* res4 = removeSmallest(nums4, 1, &returnSize);
    printArray(res4, returnSize);
    free(res4);

    int nums5[] = {};
    int* res5 = removeSmallest(nums5, 0, &returnSize);
    printArray(res5, returnSize);
    free(res5);

    return 0;
}