#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare_doubles(const void *a, const void *b) {
    double arg1 = *(const double*)a;
    double arg2 = *(const double*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

double findUniq(double arr[], int n) {
    qsort(arr, n, sizeof(double), compare_doubles);
    if (arr[0] == arr[1]) {
        return arr[n - 1];
    } else {
        return arr[0];
    }
}

int main() {
    double test1[] = {1, 1, 1, 2, 1, 1};
    double test2[] = {0, 0, 0.55, 0, 0};
    double test3[] = {2, 1, 1, 1, 1, 1};
    double test4[] = {10, 10, 10, 5, 10};
    double test5[] = {8, 8, 8, 8, 9};

    printf("%f\n", findUniq(test1, 6)); // Output: 2.000000
    printf("%f\n", findUniq(test2, 5)); // Output: 0.550000
    printf("%f\n", findUniq(test3, 6)); // Output: 2.000000
    printf("%f\n", findUniq(test4, 5)); // Output: 5.000000
    printf("%f\n", findUniq(test5, 5)); // Output: 9.000000

    return 0;
}