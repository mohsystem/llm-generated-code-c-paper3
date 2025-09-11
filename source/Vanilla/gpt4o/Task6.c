#include <stdio.h>

double findUniq(double arr[], int size) {
    if (arr[0] != arr[1] && arr[0] != arr[2]) {
        return arr[0];
    }
    for (int i = 0; i < size; i++) {
        if (arr[i] != arr[0]) {
            return arr[i];
        }
    }
    return -1; // Default return value, should never be reached
}

int main() {
    double arr1[] = {1, 1, 1, 2, 1, 1};
    double arr2[] = {0, 0, 0.55, 0, 0};
    double arr3[] = {3, 3, 3, 3, 4, 3};
    double arr4[] = {5, 6, 5, 5, 5, 5};
    double arr5[] = {7, 7, 7, 7, 7, 8};

    printf("%f\n", findUniq(arr1, 6)); // => 2
    printf("%f\n", findUniq(arr2, 5)); // => 0.55
    printf("%f\n", findUniq(arr3, 6)); // => 4
    printf("%f\n", findUniq(arr4, 6)); // => 6
    printf("%f\n", findUniq(arr5, 6)); // => 8

    return 0;
}