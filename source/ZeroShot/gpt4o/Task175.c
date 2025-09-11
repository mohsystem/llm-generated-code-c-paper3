#include <stdio.h>

typedef struct {
    int* array;
    int length;
} MountainArray;

int get(MountainArray* mountainArr, int index) {
    return mountainArr->array[index];
}

int length(MountainArray* mountainArr) {
    return mountainArr->length;
}

int findPeak(MountainArray* mountainArr, int left, int right) {
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

int binarySearch(MountainArray* mountainArr, int target, int left, int right, int ascending) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int midValue = get(mountainArr, mid);

        if (midValue == target) {
            return mid;
        }
        if (ascending) {
            if (midValue < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        } else {
            if (midValue > target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return -1;
}

int findInMountainArray(int target, MountainArray* mountainArr) {
    int peak = findPeak(mountainArr, 0, mountainArr->length - 1);

    int index = binarySearch(mountainArr, target, 0, peak, 1);
    if (index != -1) {
        return index;
    }

    return binarySearch(mountainArr, target, peak + 1, mountainArr->length - 1, 0);
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5, 3, 1};
    int arr2[] = {0, 1, 2, 4, 2, 1};
    MountainArray mountainArr1 = {arr1, 7};
    MountainArray mountainArr2 = {arr2, 6};

    printf("%d\n", findInMountainArray(3, &mountainArr1)); // Output: 2
    printf("%d\n", findInMountainArray(3, &mountainArr2)); // Output: -1
    printf("%d\n", findInMountainArray(5, &mountainArr1)); // Output: 4
    printf("%d\n", findInMountainArray(4, &mountainArr1)); // Output: 3
    printf("%d\n", findInMountainArray(1, &mountainArr2)); // Output: 1

    return 0;
}