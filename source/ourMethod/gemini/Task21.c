#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int* removeSmallest(int* numbers, int size, int* newSize) {
    if (size == 0) {
        *newSize = 0;
        return NULL;
    }

    int minVal = numbers[0];
    int minIndex = 0;
    for (int i = 1; i < size; i++) {
        if (numbers[i] < minVal) {
            minVal = numbers[i];
            minIndex = i;
        }
    }

    int* result = (int*)malloc((size - 1) * sizeof(int));
    *newSize = size - 1;
    if (!result) {
        *newSize = 0;
        return NULL; // Handle memory allocation failure
    }


    int j = 0;
    for (int i = 0; i < size; i++) {
        if (i != minIndex) {
            result[j++] = numbers[i];
        }
    }

    return result;
}

int main() {
    int test1[] = {1, 2, 3, 4, 5};
    int size1 = sizeof(test1) / sizeof(test1[0]);
    int newSize1;
    int* result1 = removeSmallest(test1, size1, &newSize1);
    for (int i = 0; i < newSize1; i++) {
        printf("%d ", result1[i]);
    }
    printf("\n"); // Output: 2 3 4 5
    free(result1);

    int test2[] = {5, 3, 2, 1, 4};
    int size2 = sizeof(test2) / sizeof(test2[0]);
    int newSize2;
    int* result2 = removeSmallest(test2, size2, &newSize2);
    for (int i = 0; i < newSize2; i++) {
        printf("%d ", result2[i]);
    }
    printf("\n"); // Output: 5 3 2 4
    free(result2);

    int test3[] = {2, 2, 1, 2, 1};
    int size3 = sizeof(test3) / sizeof(test3[0]);
    int newSize3;
    int* result3 = removeSmallest(test3, size3, &newSize3);
    for (int i = 0; i < newSize3; i++) {
        printf("%d ", result3[i]);
    }
    printf("\n"); // Output: 2 2 2 1
    free(result3);

    int test4[] = {};
    int size4 = sizeof(test4) / sizeof(test4[0]);
    int newSize4;
    int* result4 = removeSmallest(test4, size4, &newSize4);
    for (int i = 0; i < newSize4; i++) {
        printf("%d ", result4[i]);
    }
    printf("\n"); // Output:
    free(result4);


    int test5[] = {10};
    int size5 = sizeof(test5) / sizeof(test5[0]);
    int newSize5;
    int* result5 = removeSmallest(test5, size5, &newSize5);
    for (int i = 0; i < newSize5; i++) {
        printf("%d ", result5[i]);
    }
    printf("\n"); // Output:
    free(result5);

    return 0;
}