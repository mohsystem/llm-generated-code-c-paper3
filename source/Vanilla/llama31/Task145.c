#include <stdio.h>
#include <limits.h>

int maxSubArraySum(int arr[], int size) {
    int maxSum = arr[0];
    int maxEnding = arr[0];
    for (int i = 1; i < size; i++) {
        maxEnding = (maxEnding + arr[i] > arr[i]) ? maxEnding + arr[i] : arr[i];
        maxSum = (maxSum > maxEnding) ? maxSum : maxEnding;
    }
    return maxSum;
}

int main() {
    int arr1[] = {2, 3, -8, 7, -1, 2, 3};
    int arr2[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int arr3[] = {1, 2, 3, 4, 5};
    int arr4[] = {-1, -2, -3, -4, -5};
    int arr5[] = {0, 0, 0, 0, 0};

    printf("%d\n", maxSubArraySum(arr1, sizeof(arr1)/sizeof(arr1[0]))); // Output: 7
    printf("%d\n", maxSubArraySum(arr2, sizeof(arr2)/sizeof(arr2[0]))); // Output: 7
    printf("%d\n", maxSubArraySum(arr3, sizeof(arr3)/sizeof(arr3[0]))); // Output: 15
    printf("%d\n", maxSubArraySum(arr4, sizeof(arr4)/sizeof(arr4[0]))); // Output: -1
    printf("%d\n", maxSubArraySum(arr5, sizeof(arr5)/sizeof(arr5[0]))); // Output: 0

    return 0;
}