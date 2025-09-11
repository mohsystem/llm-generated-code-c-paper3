#include <stdio.h>

int findEqualSidesIndex(int arr[], int size) {
    int totalSum = 0, leftSum = 0;
    
    for (int i = 0; i < size; i++) {
        totalSum += arr[i];
    }
    
    for (int i = 0; i < size; i++) {
        totalSum -= arr[i];
        if (leftSum == totalSum) {
            return i;
        }
        leftSum += arr[i];
    }
    
    return -1;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 3, 2, 1};
    int arr2[] = {1, 100, 50, -51, 1, 1};
    int arr3[] = {20, 10, -80, 10, 10, 15, 35};
    int arr4[] = {1, 2, 3, 4, 5, 6};
    int arr5[] = {10, -10, 10, -10, 10, -10, 10};
    
    printf("%d\n", findEqualSidesIndex(arr1, 7)); // Output: 3
    printf("%d\n", findEqualSidesIndex(arr2, 6)); // Output: 1
    printf("%d\n", findEqualSidesIndex(arr3, 7)); // Output: 0
    printf("%d\n", findEqualSidesIndex(arr4, 6)); // Output: -1
    printf("%d\n", findEqualSidesIndex(arr5, 7)); // Output: 0

    return 0;
}