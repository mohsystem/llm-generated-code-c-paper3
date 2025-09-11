#include <stdio.h>
#include <stdlib.h>

int* removeSmallest(const int* numbers, int length, int* newLength) {
    if (length == 0) {
        *newLength = 0;
        return NULL;
    }

    int minIndex = 0;
    for (int i = 1; i < length; i++) {
        if (numbers[i] < numbers[minIndex]) {
            minIndex = i;
        }
    }

    *newLength = length - 1;
    int* result = (int*)malloc(*newLength * sizeof(int));

    for (int i = 0, j = 0; i < length; i++) {
        if (i != minIndex) {
            result[j++] = numbers[i];
        }
    }

    return result;
}

void printArray(const int* arr, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int newLength;
    int* result;

    int nums1[] = {1, 2, 3, 4, 5};
    result = removeSmallest(nums1, 5, &newLength);
    printArray(result, newLength);
    free(result);

    int nums2[] = {5, 3, 2, 1, 4};
    result = removeSmallest(nums2, 5, &newLength);
    printArray(result, newLength);
    free(result);

    int nums3[] = {2, 2, 1, 2, 1};
    result = removeSmallest(nums3, 5, &newLength);
    printArray(result, newLength);
    free(result);

    int nums4[] = {1};
    result = removeSmallest(nums4, 1, &newLength);
    printArray(result, newLength);
    free(result);

    int nums5[] = {};
    result = removeSmallest(nums5, 0, &newLength);
    printArray(result, newLength);
    free(result);

    return 0;
}