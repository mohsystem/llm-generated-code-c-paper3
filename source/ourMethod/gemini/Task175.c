//  This is MountainArray's API interface.
// You should not implement it, or speculate about its implementation
// struct MountainArray {
//    int (*get)(struct MountainArray *, int);
//    int (*length)(struct MountainArray *);
// };



#include <stdio.h>

// Mock MountainArray for testing
typedef struct {
    int *arr;
    int size;
} MountainArrayImpl;

int get(MountainArrayImpl *mountainArr, int index) {
    return mountainArr->arr[index];
}

int length(MountainArrayImpl *mountainArr) {
    return mountainArr->size;
}


int findPeakIndex(MountainArrayImpl* mountainArr, int left, int right) {
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

int findTarget(MountainArrayImpl* mountainArr, int target, int left, int right, int ascending) {
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


int findInMountainArray(int target, MountainArrayImpl* mountainArr) {
    int n = length(mountainArr);
    int peakIndex = findPeakIndex(mountainArr, 0, n - 1);

    int leftIndex = findTarget(mountainArr, target, 0, peakIndex, 1);
    if (leftIndex != -1) {
        return leftIndex;
    }

    return findTarget(mountainArr, target, peakIndex + 1, n - 1, 0);
}


int main() {
    // Test cases
    int arr1[] = {1, 2, 3, 4, 5, 3, 1};
    MountainArrayImpl mountainArr1 = {arr1, sizeof(arr1) / sizeof(arr1[0])};
    int target1 = 3;
    printf("%d\n", findInMountainArray(target1, &mountainArr1)); // Output: 2

    int arr2[] = {0, 1, 2, 4, 2, 1};
    MountainArrayImpl mountainArr2 = {arr2, sizeof(arr2) / sizeof(arr2[0])};
    int target2 = 3;
    printf("%d\n", findInMountainArray(target2, &mountainArr2)); // Output: -1

    int arr3[] = {1, 5, 2};
    MountainArrayImpl mountainArr3 = {arr3, sizeof(arr3) / sizeof(arr3[0])};
    int target3 = 2;
    printf("%d\n", findInMountainArray(target3, &mountainArr3)); // Output: 2

    int arr4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    MountainArrayImpl mountainArr4 = {arr4, sizeof(arr4) / sizeof(arr4[0])};
    int target4 = 0;
    printf("%d\n", findInMountainArray(target4, &mountainArr4)); // Output: 19

    int arr5[] = {0, 5, 3, 1};
    MountainArrayImpl mountainArr5 = {arr5, sizeof(arr5) / sizeof(arr5[0])};
    int target5 = 1;
    printf("%d\n", findInMountainArray(target5, &mountainArr5)); // Output: 3

    return 0;
}