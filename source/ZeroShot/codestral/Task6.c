#include <stdio.h>
#include <stdlib.h>

double findUniq(double arr[], int size) {
    qsort(arr, size, sizeof(double), compare);
    if (arr[0] == arr[1]) {
        return arr[size - 1];
    } else {
        return arr[0];
    }
}

int compare(const void *a, const void *b) {
    return (*(double*)a - *(double*)b);
}

int main() {
    double arr1[] = {1, 1, 1, 2, 1, 1};
    double arr2[] = {0, 0, 0.55, 0, 0};
    printf("%f\n", findUniq(arr1, 6)); // => 2.000000
    printf("%f\n", findUniq(arr2, 5)); // => 0.550000
    return 0;
}