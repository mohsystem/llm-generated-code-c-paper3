#include <stdio.h>

int findEqualSumIndex(int arr[], int length) {
    int totalSum = 0;
    for (int i = 0; i < length; i++) {
        totalSum += arr[i];
    }
    
    int leftSum = 0;
    for (int i = 0; i < length; i++) {
        int rightSum = totalSum - leftSum - arr[i];
        if (leftSum == rightSum) {
            return i;
        }
        leftSum += arr[i];
    }
    
    return -1;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 3, 2, 1};
    printf("%d\n", findEqualSumIndex(arr1, 7)); // 3

    int arr2[] = {1, 100, 50, -51, 1, 1};
    printf("%d\n", findEqualSumIndex(arr2, 6)); // 1

    int arr3[] = {20, 10, -80, 10, 10, 15, 35};
    printf("%d\n", findEqualSumIndex(arr3, 7)); // 0

    int arr4[] = {1, 2, 3, 4, 5, 6};
    printf("%d\n", findEqualSumIndex(arr4, 6)); // -1

    int arr5[] = {0, 0, 0, 0, 0, 0};
    printf("%d\n", findEqualSumIndex(arr5, 6)); // 0

    return 0;
}