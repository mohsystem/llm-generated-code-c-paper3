// Note: C does not support classes or objects like the other languages.
// This implementation is simplified and does not use the MountainArray interface.
// It assumes direct access to the array.

#include <stdio.h>

int findPeak(int* arr, int left, int right) {
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < arr[mid + 1]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int binarySearch(int* arr, int left, int right, int target, int isAscending) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int midVal = arr[mid];
        if (midVal == target) return mid;
        if (isAscending) {
            if (midVal < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        } else {
            if (midVal < target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
    }
    return -1;
}

int findInMountainArray(int target, int* arr, int n) {
    int peak = findPeak(arr, 0, n - 1);
    int index = binarySearch(arr, 0, peak, target, 1);
    if (index != -1) return index;
    return binarySearch(arr, peak, n - 1, target, 0);
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5, 3, 1};
    printf("%d\n", findInMountainArray(3, arr1, sizeof(arr1) / sizeof(arr1[0]))); // Output: 2

    int arr2[] = {0, 1, 2, 4, 2, 1};
    printf("%d\n", findInMountainArray(3, arr2, sizeof(arr2) / sizeof(arr2[0]))); // Output: -1

    int arr3[] = {3, 5, 1};
    printf("%d\n", findInMountainArray(3, arr3, sizeof(arr3) / sizeof(arr3[0]))); // Output: 0

    int arr4[] = {1, 2, 3, 4, 5, 2, 1, 0};
    printf("%d\n", findInMountainArray(3, arr4, sizeof(arr4) / sizeof(arr4[0]))); // Output: 2

    int arr5[] = {0, 1, 2, 3, 4, 5, 4, 3, 2, 1};
    printf("%d\n", findInMountainArray(0, arr5, sizeof(arr5) / sizeof(arr5[0]))); // Output: 0

    return 0;
}