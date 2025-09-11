#include <stdio.h>
#include <stdlib.h>

int compare_doubles(const void *a, const void *b) {
    double arg1 = *(const double*)a;
    double arg2 = *(const double*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

double findUniq(double arr[], size_t n) {
    if (n < 3) {
       fprintf(stderr,"Array must contain at least 3 numbers.\n");
       exit(1); // Indicate an error 
    }

    qsort(arr, n, sizeof(double), compare_doubles);

    if (arr[0] != arr[1]) {
        return arr[0];
    } else {
        return arr[n - 1];
    }
}

int main() {
    double test1[] = {1, 1, 1, 2, 1, 1};
    double test2[] = {0, 0, 0.55, 0, 0};
    double test3[] = {2, 1, 1, 1, 1, 1};
    double test4[] = {10, 10, 5, 10, 10};
    double test5[] = {8, 8, 8, 8, 7};

    printf("%f\n", findUniq(test1, sizeof(test1)/sizeof(test1[0]))); // Output: 2.000000
    printf("%f\n", findUniq(test2, sizeof(test2)/sizeof(test2[0]))); // Output: 0.550000
    printf("%f\n", findUniq(test3, sizeof(test3)/sizeof(test3[0]))); // Output: 2.000000
    printf("%f\n", findUniq(test4, sizeof(test4)/sizeof(test4[0]))); // Output: 5.000000
    printf("%f\n", findUniq(test5, sizeof(test5)/sizeof(test5[0]))); // Output: 7.000000

    return 0;
}