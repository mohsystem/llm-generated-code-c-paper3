#include <stdio.h>

double findUniq(const double arr[], int size) {
    double unique = arr[0];
    if (arr[0] != arr[1] && arr[0] != arr[2]) {
        unique = arr[0];
    } else {
        for (int i = 1; i < size; i++) {
            if (arr[i] != arr[0]) {
                unique = arr[i];
                break;
            }
        }
    }
    return unique;
}

int main() {
    double arr1[] = {1, 1, 1, 2, 1, 1};
    double arr2[] = {0, 0, 0.55, 0, 0};
    double arr3[] = {5, 5, 5, 5, 3};
    double arr4[] = {10, 10, 10, 20};
    double arr5[] = {7, 8, 7, 7, 7};

    printf("%f\n", findUniq(arr1, 6)); // => 2
    printf("%f\n", findUniq(arr2, 5)); // => 0.55
    printf("%f\n", findUniq(arr3, 5)); // => 3
    printf("%f\n", findUniq(arr4, 4)); // => 20
    printf("%f\n", findUniq(arr5, 5)); // => 8

    return 0;
}