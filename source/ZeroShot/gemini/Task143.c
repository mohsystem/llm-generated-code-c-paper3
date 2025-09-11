#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void sort_array(int arr[], int n) {
    qsort(arr, n, sizeof(int), compare);
}

int main() {
    int test1[] = {5, 2, 8, 1, 9, 4};
    int n1 = sizeof(test1) / sizeof(test1[0]);
    sort_array(test1, n1);
    for (int i = 0; i < n1; i++) printf("%d ", test1[i]);
    printf("\n"); // Expected: 1 2 4 5 8 9

    int test2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(test2) / sizeof(test2[0]);
    sort_array(test2, n2);
    for (int i = 0; i < n2; i++) printf("%d ", test2[i]);
    printf("\n"); // Expected: 1 2 3 4 5

    int test3[] = {5, 4, 3, 2, 1};
    int n3 = sizeof(test3) / sizeof(test3[0]);
    sort_array(test3, n3);
    for (int i = 0; i < n3; i++) printf("%d ", test3[i]);
    printf("\n"); // Expected: 1 2 3 4 5


    int test4[] = {};
    int n4 = sizeof(test4) / sizeof(test4[0]);
    sort_array(test4, n4);
    for (int i = 0; i < n4; i++) printf("%d ", test4[i]);
    printf("\n"); // Expected:


    int test5[] = {0, 0, 0, 0};
    int n5 = sizeof(test5) / sizeof(test5[0]);
    sort_array(test5, n5);
    for (int i = 0; i < n5; i++) printf("%d ", test5[i]);
    printf("\n"); // Expected: 0 0 0 0

    return 0;
}