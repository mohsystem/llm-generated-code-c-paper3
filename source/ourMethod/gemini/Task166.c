#include <stdio.h>
#include <stdlib.h>

// Compare function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}


int *posNegSort(int nums[], int size, int *result_size) {
    if (size == 0) {
        *result_size = 0;
        return NULL;
    }

    int *positiveNums = (int *)malloc(size * sizeof(int));
    int positiveCount = 0;
    int *result = (int *)malloc(size * sizeof(int));
    *result_size = size;

    for (int i = 0; i < size; i++) {
        if (nums[i] > 0) {
            positiveNums[positiveCount++] = nums[i];
        }
    }

    qsort(positiveNums, positiveCount, sizeof(int), compare);

    int positiveIndex = 0;
    for (int i = 0; i < size; i++) {
        if (nums[i] > 0) {
            result[i] = positiveNums[positiveIndex++];
        } else {
            result[i] = nums[i];
        }
    }

    free(positiveNums);
    return result;
}

int main() {
    int test1[] = {6, 3, -2, 5, -8, 2, -2};
    int size1 = sizeof(test1) / sizeof(test1[0]);
    int result_size1;
    int *result1 = posNegSort(test1, size1, &result_size1);
    for (int i = 0; i < result_size1; i++) printf("%d ", result1[i]);
    printf("\n");
    free(result1);

    int test2[] = {6, 5, 4, -1, 3, 2, -1, 1};
    int size2 = sizeof(test2) / sizeof(test2[0]);
    int result_size2;
    int *result2 = posNegSort(test2, size2, &result_size2);
    for (int i = 0; i < result_size2; i++) printf("%d ", result2[i]);
    printf("\n");
    free(result2);


    int test3[] = {-5, -5, -5, -5, 7, -5};
    int size3 = sizeof(test3) / sizeof(test3[0]);
    int result_size3;
    int *result3 = posNegSort(test3, size3, &result_size3);
    for (int i = 0; i < result_size3; i++) printf("%d ", result3[i]);
    printf("\n");
    free(result3);


    int test4[] = {};
    int size4 = sizeof(test4) / sizeof(test4[0]);
    int result_size4;
    int *result4 = posNegSort(test4, size4, &result_size4);
    for (int i = 0; i < result_size4; i++) printf("%d ", result4[i]);
    printf("\n");
    
    int test5[] = {1, 2, 3, 4, 5};
    int size5 = sizeof(test5) / sizeof(test5[0]);
    int result_size5;
    int *result5 = posNegSort(test5, size5, &result_size5);
    for (int i = 0; i < result_size5; i++) printf("%d ", result5[i]);
    printf("\n");
    free(result5);

    return 0;
}