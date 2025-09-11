#include<stdio.h>

double findUniq(double arr[], int size) {
    if (arr[0] != arr[1]) {
        if (arr[0] != arr[2]) {
            return arr[0];
        } else {
            return arr[1];
        }
    }
    for (int i = 2; i < size; i++) {
        if (arr[i] != arr[0]) {
            return arr[i];
        }
    }
    return -1;  // Return -1 if no unique number is found
}

int main() {
    double arr1[] = {1, 1, 1, 2, 1, 1};
    double arr2[] = {0, 0, 0.55, 0, 0};
    printf("%lf\n", findUniq(arr1, 6));  // => 2.0
    printf("%lf\n", findUniq(arr2, 5));  // => 0.55
    return 0;
}