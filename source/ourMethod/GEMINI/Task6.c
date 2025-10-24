#include <stdio.h>
#include <stdlib.h> // For size_t

double findUniq(const double arr[], size_t n) {
    // The array is guaranteed to have at least 3 elements.
    // We compare the first three elements to determine the common number.
    if (arr[0] != arr[1]) {
        // If the first two are different, the third element will match one of them.
        // The one that doesn't match is the unique number.
        return arr[0] == arr[2] ? arr[1] : arr[0];
    } else {
        // If the first two are the same, this is the common number.
        // We then iterate through the rest of the array to find the different one.
        double common = arr[0];
        for (size_t i = 2; i < n; ++i) {
            if (arr[i] != common) {
                return arr[i];
            }
        }
    }
    // This part is unreachable under the problem's guarantees.
    return 0.0;
}

int main() {
    // Test cases
    double test1[] = { 1, 1, 1, 2, 1, 1 };
    printf("%.10g\n", findUniq(test1, sizeof(test1)/sizeof(test1[0])));

    double test2[] = { 0, 0, 0.55, 0, 0 };
    printf("%.10g\n", findUniq(test2, sizeof(test2)/sizeof(test2[0])));

    double test3[] = { 3, 10, 3, 3, 3 };
    printf("%.10g\n", findUniq(test3, sizeof(test3)/sizeof(test3[0])));

    double test4[] = { 5, 5, 5, 5, 0.2 };
    printf("%.10g\n", findUniq(test4, sizeof(test4)/sizeof(test4[0])));

    double test5[] = { -2, -2, -2, -1, -2 };
    printf("%.10g\n", findUniq(test5, sizeof(test5)/sizeof(test5[0])));

    return 0;
}