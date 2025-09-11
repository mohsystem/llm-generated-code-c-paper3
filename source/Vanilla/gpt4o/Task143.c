#include <stdio.h>
#include <stdlib.h>

int compare(const void * a, const void * b) {
    return (*(int*)a - *(int*)b);
}

void sortArray(int arr[], int size) {
    qsort(arr, size, sizeof(int), compare);
}

int main() {
    int test1[] = {5, 2, 9, 1, 5, 6};
    int test2[] = {3, 0, -2, 5, 1, 2};
    int test3[] = {1, 2, 3, 4, 5};
    int test4[] = {5, 4, 3, 2, 1};
    int test5[] = {10, 8, 12, 15, 3};

    int sizes[] = {6, 6, 5, 5, 5};

    sortArray(test1, sizes[0]);
    sortArray(test2, sizes[1]);
    sortArray(test3, sizes[2]);
    sortArray(test4, sizes[3]);
    sortArray(test5, sizes[4]);

    for (int i = 0; i < sizes[0]; i++) printf("%d ", test1[i]);
    printf("\n");
    for (int i = 0; i < sizes[1]; i++) printf("%d ", test2[i]);
    printf("\n");
    for (int i = 0; i < sizes[2]; i++) printf("%d ", test3[i]);
    printf("\n");
    for (int i = 0; i < sizes[3]; i++) printf("%d ", test4[i]);
    printf("\n");
    for (int i = 0; i < sizes[4]; i++) printf("%d ", test5[i]);
    printf("\n");

    return 0;
}