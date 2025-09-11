#include <stdio.h>

int findEvenIndex(int arr[], int length) {
    int totalSum = 0;
    for (int i = 0; i < length; i++) {
        totalSum += arr[i];
    }
    
    int leftSum = 0;
    for (int i = 0; i < length; i++) {
        if (leftSum == totalSum - leftSum - arr[i]) {
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
    int arr5[] = {-1, -2, -3, -4, -3, -2, -1};

    printf("%d\n", findEvenIndex(arr1, 7)); // Output: 3
    printf("%d\n", findEvenIndex(arr2, 6)); // Output: 1
    printf("%d\n", findEvenIndex(arr3, 7)); // Output: 0
    printf("%d\n", findEvenIndex(arr4, 6)); // Output: -1
    printf("%d\n", findEvenIndex(arr5, 7)); // Output: 3

    return 0;
}