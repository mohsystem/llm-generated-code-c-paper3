#include <stdio.h>

typedef struct {
    int *array;
    int length;
} MountainArray;

int get(MountainArray *mountainArr, int index) {
    return mountainArr->array[index];
}

int length(MountainArray *mountainArr) {
    return mountainArr->length;
}

int findPeak(MountainArray *mountainArr) {
    int left = 0, right = length(mountainArr) - 1;
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

int binarySearch(MountainArray *mountainArr, int target, int left, int right, int ascending) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int value = get(mountainArr, mid);
        if (value == target) return mid;
        if (ascending) {
            if (value < target) left = mid + 1;
            else right = mid - 1;
        } else {
            if (value > target) left = mid + 1;
            else right = mid - 1;
        }
    }
    return -1;
}

int findInMountainArray(int target, MountainArray *mountainArr) {
    int peak = findPeak(mountainArr);
    int index = binarySearch(mountainArr, target, 0, peak, 1);
    if (index != -1) return index;
    return binarySearch(mountainArr, target, peak + 1, length(mountainArr) - 1, 0);
}

int main() {
    int array1[] = {1, 2, 3, 4, 5, 3, 1};
    MountainArray arr1 = {array1, sizeof(array1) / sizeof(array1[0])};

    int array2[] = {0, 1, 2, 4, 2, 1};
    MountainArray arr2 = {array2, sizeof(array2) / sizeof(array2[0])};

    printf("%d\n", findInMountainArray(3, &arr1)); // Output: 2
    printf("%d\n", findInMountainArray(3, &arr2)); // Output: -1
    printf("%d\n", findInMountainArray(5, &arr1)); // Output: 4
    printf("%d\n", findInMountainArray(2, &arr1)); // Output: 1
    printf("%d\n", findInMountainArray(0, &arr2)); // Output: 0

    return 0;
}