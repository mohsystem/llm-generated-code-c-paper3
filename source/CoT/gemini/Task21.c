#include <stdio.h>
#include <stdlib.h>

int* removeSmallest(int* numbers, int size) {
    if (size == 0) {
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
    if(result == NULL) {
        return NULL; // Memory allocation failed
    }

    for (int i = 0, j = 0; i < size; i++) {
        if (i != minIndex) {
            result[j++] = numbers[i];
        }
    }
    return result;
}

int main() {
    int test1[] = {1, 2, 3, 4, 5};
    int size1 = sizeof(test1) / sizeof(test1[0]);
    int* result1 = removeSmallest(test1, size1);
    for (int i = 0; i < size1 - 1; i++) printf("%d ", result1[i]);
    printf("\n");
    free(result1);

    int test2[] = {5, 3, 2, 1, 4};
    int size2 = sizeof(test2) / sizeof(test2[0]);
    int* result2 = removeSmallest(test2, size2);
    for (int i = 0; i < size2 - 1; i++) printf("%d ", result2[i]);
    printf("\n");
    free(result2);

    int test3[] = {2, 2, 1, 2, 1};
    int size3 = sizeof(test3) / sizeof(test3[0]);
    int* result3 = removeSmallest(test3, size3);
    for (int i = 0; i < size3 - 1; i++) printf("%d ", result3[i]);
    printf("\n");
    free(result3);

    int test4[] = {};
    int size4 = sizeof(test4) / sizeof(test4[0]);
    int *result4 = removeSmallest(test4, size4);
    if (result4 == NULL) {
        printf("\n");
    }

     int test5[] = {5};
    int size5 = sizeof(test5) / sizeof(test5[0]);
    int *result5 = removeSmallest(test5, size5);
    if (result5 == NULL) {
        printf("\n");
    }

    return 0;
}