#include <stdio.h>
#include <stdlib.h>

int compare_doubles(const void *a, const void *b) {
    double arg1 = *(const double*)a;
    double arg2 = *(const double*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

double findUniq(double arr[], int n) {
    qsort(arr, n, sizeof(double), compare_doubles);
    return arr[0] == arr[1] ? arr[n - 1] : arr[0];
}

int main() {
    double arr1[] = {1, 1, 1, 2, 1, 1};
    printf("%f\n", findUniq(arr1, 6)); // => 2

    double arr2[] = {0, 0, 0.55, 0, 0};
    printf("%f\n", findUniq(arr2, 5)); // => 0.55

    double arr3[] = {2, 1, 1, 1, 1, 1};
    printf("%f\n", findUniq(arr3, 6)); // => 2

    double arr4[] = {10, 3, 3, 3, 3};
    printf("%f\n", findUniq(arr4, 5)); // => 10

    double arr5[] = {8, 8, 8, 8, 7};
    printf("%f\n", findUniq(arr5, 5)); // => 7

    return 0;
}