#include <stdio.h>

int findEvenIndex(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int leftSum = 0;
        for (int j = 0; j < i; j++) {
            leftSum += arr[j];
        }
        int rightSum = 0;
        for (int j = i + 1; j < n; j++) {
            rightSum += arr[j];
        }
        if (leftSum == rightSum) {
            return i;
        }
    }
    return -1;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 3, 2, 1};
    printf("%d\n", findEvenIndex(arr1, 7)); // 3

    int arr2[] = {1, 100, 50, -51, 1, 1};
    printf("%d\n", findEvenIndex(arr2, 6)); // 1

    int arr3[] = {20, 10, -80, 10, 10, 15, 35};
    printf("%d\n", findEvenIndex(arr3, 7)); // 0

    int arr4[] = {1, 2, 3, 4, 5};
    printf("%d\n", findEvenIndex(arr4, 5)); // -1

    int arr5[] = {1};
    printf("%d\n", findEvenIndex(arr5, 1)); // 0

    return 0;
}