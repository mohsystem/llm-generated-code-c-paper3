#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void sort_array(int *arr, int n) {
    qsort(arr, n, sizeof(int), compare);
}

int main() {
    int test1[] = {5, 2, 8, 1, 9, 4};
    int n1 = sizeof(test1) / sizeof(test1[0]);
    sort_array(test1, n1);
    for (int i = 0; i < n1; i++) printf("%d ", test1[i]); // Output: 1 2 4 5 8 9
    printf("\n");

    int test2[] = {10, -5, 0, 3, -2};
    int n2 = sizeof(test2) / sizeof(test2[0]);
    sort_array(test2, n2);
    for (int i = 0; i < n2; i++) printf("%d ", test2[i]); // Output: -5 -2 0 3 10
    printf("\n");

    int test3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(test3) / sizeof(test3[0]);
    sort_array(test3, n3);
    for (int i = 0; i < n3; i++) printf("%d ", test3[i]); // Output: 1 2 3 4 5
    printf("\n");

    int test4[] = {};
    int n4 = sizeof(test4) / sizeof(test4[0]);
    sort_array(test4, n4);
    for (int i = 0; i < n4; i++) printf("%d ", test4[i]); // Output:
    printf("\n");

    int test5[] = {5};
    int n5 = sizeof(test5) / sizeof(test5[0]);
    sort_array(test5, n5);
    for (int i = 0; i < n5; i++) printf("%d ", test5[i]); // Output: 5
    printf("\n");


    return 0;
}