#include <stdio.h>

int findMissingNumber(int nums[], int n, int size) {
    int expectedSum = n * (n + 1) / 2;
    int actualSum = 0;
    for (int i = 0; i < size; i++) {
        actualSum += nums[i];
    }
    return expectedSum - actualSum;
}

int main() {
    int arr1[] = {1, 2, 4, 5, 6};
    int arr2[] = {1, 3, 4, 5};
    int arr3[] = {2, 3, 4, 5};
    int arr4[] = {1, 2, 3, 5};
    int arr5[] = {1, 2, 3, 4};

    printf("%d\n", findMissingNumber(arr1, 6, 5)); // 3
    printf("%d\n", findMissingNumber(arr2, 5, 4)); // 2
    printf("%d\n", findMissingNumber(arr3, 5, 4)); // 1
    printf("%d\n", findMissingNumber(arr4, 5, 4)); // 4
    printf("%d\n", findMissingNumber(arr5, 5, 4)); // 5

    return 0;
}