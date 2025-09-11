#include <stdio.h>
#include <stdlib.h>

// Define the MountainArray interface (mimicking it for testing)
typedef struct {
    int *arr;
    int size;
} MountainArray;

int get(MountainArray *mountainArr, int index) {
    return mountainArr->arr[index];
}

int length(MountainArray *mountainArr) {
    return mountainArr->size;
}


int findPeakIndex(MountainArray *mountainArr) {
    int n = length(mountainArr);
    int left = 0, right = n - 1;
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

int binarySearch(MountainArray *mountainArr, int left, int right, int target, int ascending) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int val = get(mountainArr, mid);
        if (val == target) {
            return mid;
        } else if (ascending && val < target || !ascending && val > target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int findInMountainArray(int target, MountainArray *mountainArr) {
    int n = length(mountainArr);
    int peakIndex = findPeakIndex(mountainArr);

    int leftIndex = binarySearch(mountainArr, 0, peakIndex, target, 1);
    if (leftIndex != -1) {
        return leftIndex;
    }

    return binarySearch(mountainArr, peakIndex + 1, n - 1, target, 0);
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5, 3, 1};
    MountainArray mountainArr1 = {arr1, sizeof(arr1) / sizeof(arr1[0])};
    printf("Test Case 1: %d\n", findInMountainArray(3, &mountainArr1));

    int arr2[] = {0, 1, 2, 4, 2, 1};
    MountainArray mountainArr2 = {arr2, sizeof(arr2) / sizeof(arr2[0])};
    printf("Test Case 2: %d\n", findInMountainArray(3, &mountainArr2));
    
    int arr3[] = {1, 5, 2};
    MountainArray mountainArr3 = {arr3, sizeof(arr3) / sizeof(arr3[0])};
    printf("Test Case 3: %d\n", findInMountainArray(2, &mountainArr3));

    int arr4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    MountainArray mountainArr4 = {arr4, sizeof(arr4) / sizeof(arr4[0])};
    printf("Test Case 4: %d\n", findInMountainArray(9, &mountainArr4));

    int arr5[] = {1, 2, 3, 4, 5, 3, 1};
    MountainArray mountainArr5 = {arr5, sizeof(arr5) / sizeof(arr5[0])};
    printf("Test Case 5: %d\n", findInMountainArray(0, &mountainArr5));

    return 0;
}