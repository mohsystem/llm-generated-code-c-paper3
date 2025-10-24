#include <stdio.h>
#include <stddef.h>
#include <math.h>

double findUniq(const double* arr, size_t n) {
    if (arr == NULL || n < 3) {
        return NAN;
    }
    double a = arr[0], b = arr[1], c = arr[2];
    double common = (a == b || a == c) ? a : b;
    for (size_t i = 0; i < n; ++i) {
        if (arr[i] != common) {
            return arr[i];
        }
    }
    return NAN;
}

int main(void) {
    double t1[] = {1, 1, 1, 2, 1, 1};
    double t2[] = {0, 0, 0.55, 0, 0};
    double t3[] = {3, 3, 4, 3, 3, 3};
    double t4[] = {9, 8, 8, 8, 8, 8};
    double t5[] = {-1, -1, -1, -2, -1, -1};

    printf("%.15g\n", findUniq(t1, sizeof(t1)/sizeof(t1[0])));
    printf("%.15g\n", findUniq(t2, sizeof(t2)/sizeof(t2[0])));
    printf("%.15g\n", findUniq(t3, sizeof(t3)/sizeof(t3[0])));
    printf("%.15g\n", findUniq(t4, sizeof(t4)/sizeof(t4[0])));
    printf("%.15g\n", findUniq(t5, sizeof(t5)/sizeof(t5[0])));

    return 0;
}