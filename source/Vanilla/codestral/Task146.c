#include <stdio.h>

int findMissingNumber(int arr[], int n) {
    int sum = (n + 1) * (n + 2) / 2;
    for (int i = 0; i < n; i++) {
        sum -= arr[i];
    }
    return sum;
}

int main() {
    int arr1[] = {1, 2, 3, 5};
    int arr2[] = {2, 3, 4, 5, 6, 8};
    int arr3[] = {1, 2, 3, 4, 6, 7, 8};
    int arr4[] = {1, 2, 3, 4, 5, 6, 8, 9, 10};
    int arr5[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};

    printf("%d\n", findMissingNumber(arr1, 4)); // Output: 4
    printf("%d\n", findMissingNumber(arr2, 6)); // Output: 1
    printf("%d\n", findMissingNumber(arr3, 7)); // Output: 5
    printf("%d\n", findMissingNumber(arr4, 9)); // Output: 7
    printf("%d\n", findMissingNumber(arr5, 9)); // Output: 1

    return 0;
}