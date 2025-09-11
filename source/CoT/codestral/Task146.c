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
    int arr2[] = {1, 2, 4, 5, 6};
    int arr3[] = {2, 3, 4, 5, 6};
    int arr4[] = {1, 3, 4, 5, 6};
    int arr5[] = {1, 2, 3, 4};
    printf("%d\n", findMissingNumber(arr1, 4)); // Output: 4
    printf("%d\n", findMissingNumber(arr2, 5)); // Output: 3
    printf("%d\n", findMissingNumber(arr3, 5)); // Output: 1
    printf("%d\n", findMissingNumber(arr4, 5)); // Output: 2
    printf("%d\n", findMissingNumber(arr5, 4)); // Output: 5
    return 0;
}