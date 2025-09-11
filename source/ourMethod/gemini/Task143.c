#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int *sortArray(int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return NULL;
    }
    
    int *sortedArr = (int *)malloc(size * sizeof(int));
    if (sortedArr == NULL) {
        return NULL; // Handle memory allocation failure
    }

    for (int i = 0; i < size; i++) {
        sortedArr[i] = arr[i];
    }

    qsort(sortedArr, size, sizeof(int), compare);
    return sortedArr;
}

int main() {
    int test1[] = {5, 2, 8, 1, 9, 4};
    int size1 = sizeof(test1) / sizeof(test1[0]);
    int *sortedTest1 = sortArray(test1, size1);
    for (int i = 0; i < size1; i++) printf("%d ", sortedTest1[i]); // Expected: 1 2 4 5 8 9
    printf("\n");
    free(sortedTest1);

    int test2[] = {1, 2, 3, 4, 5};
    int size2 = sizeof(test2) / sizeof(test2[0]);
    int *sortedTest2 = sortArray(test2, size2);
    for (int i = 0; i < size2; i++) printf("%d ", sortedTest2[i]); // Expected: 1 2 3 4 5
    printf("\n");
    free(sortedTest2);

    int test3[] = {5, 4, 3, 2, 1};
    int size3 = sizeof(test3) / sizeof(test3[0]);
    int *sortedTest3 = sortArray(test3, size3);
    for (int i = 0; i < size3; i++) printf("%d ", sortedTest3[i]); // Expected: 1 2 3 4 5
    printf("\n");
    free(sortedTest3);

    int test4[] = {};
    int size4 = sizeof(test4) / sizeof(test4[0]);
    int *sortedTest4 = sortArray(test4, size4);
    if (sortedTest4 != NULL) {
         for (int i = 0; i < size4; i++) printf("%d ", sortedTest4[i]);
         free(sortedTest4);
    }
    printf("\n");


    int *test5 = NULL;
    int *sortedTest5 = sortArray(test5, 0); // Size 0 because test5 is NULL
    if (sortedTest5 == NULL) {
        printf("null\n"); // Expected: (null)
    }


    return 0;
}