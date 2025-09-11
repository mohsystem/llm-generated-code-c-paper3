#include <stdio.h>

int busStop(int arr[][2], int n) {
    int people = 0;
    for (int i = 0; i < n; i++) {
        people += arr[i][0] - arr[i][1];
    }
    return people;
}

int main() {
    int arr1[][2] = {{10, 0}, {3, 5}, {5, 8}};
    int arr2[][2] = {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}};
    printf("%d\n", busStop(arr1, 3));  // Expected output: 5
    printf("%d\n", busStop(arr2, 6));  // Expected output: 17
    return 0;
}