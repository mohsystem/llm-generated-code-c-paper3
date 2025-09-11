#include <stdio.h>

typedef struct MountainArray {
    int *arr;
    int n;
} MountainArray;

int get(MountainArray *mountainArr, int index) {
    return mountainArr->arr[index];
}

int length(MountainArray *mountainArr) {
    return mountainArr->n;
}

int findPeak(MountainArray *mountainArr, int left, int right) {
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (get(mountainArr, mid) < get(mountainArr, mid + 1)) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int binarySearch(MountainArray *mountainArr, int left, int right, int target, int isIncreasing) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int midValue = get(mountainArr, mid);
        if (midValue == target) return mid;
        if (isIncreasing) {
            if (midValue < target) left = mid + 1;
            else right = mid - 1;
        } else {
            if (midValue < target) right = mid - 1;
            else left = mid + 1;
        }
    }
    return -1;
}

int findInMountainArray(int target, MountainArray *mountainArr) {
    int n = length(mountainArr);
    int peakIndex = findPeak(mountainArr, 0, n - 1);
    int index = binarySearch(mountainArr, 0, peakIndex, target, 1);
    if (index != -1) return index;
    return binarySearch(mountainArr, peakIndex, n - 1, target, 0);
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5, 3, 1};
    MountainArray mountainArr1 = {arr1, sizeof(arr1) / sizeof(arr1[0])};
    printf("%d\n", findInMountainArray(3, &mountainArr1)); // Output: 2

    int arr2[] = {0, 1, 2, 4, 2, 1};
    MountainArray mountainArr2 = {arr2, sizeof(arr2) / sizeof(arr2[0])};
    printf("%d\n", findInMountainArray(3, &mountainArr2)); // Output: -1

    return 0;
}