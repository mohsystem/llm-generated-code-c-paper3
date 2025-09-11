#include <stdio.h>

typedef struct {
    int* arr;
    int n;
} MountainArray;

int get(MountainArray* mountainArr, int index) {
    return mountainArr->arr[index];
}

int length(MountainArray* mountainArr) {
    return mountainArr->n;
}

int findPeak(MountainArray* mountainArr, int l, int r) {
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (get(mountainArr, mid) < get(mountainArr, mid + 1)) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}

int binarySearch(MountainArray* mountainArr, int l, int r, int target, int ascending) {
    while (l <= r) {
        int mid = l + (r - l) / 2;
        int midVal = get(mountainArr, mid);
        if (midVal == target) return mid;
        if (ascending) {
            if (midVal < target) l = mid + 1;
            else r = mid - 1;
        } else {
            if (midVal < target) r = mid - 1;
            else l = mid + 1;
        }
    }
    return -1;
}

int findInMountainArray(int target, MountainArray* mountainArr) {
    int n = length(mountainArr);
    int peak = findPeak(mountainArr, 0, n - 1);
    int index = binarySearch(mountainArr, 0, peak, target, 1);
    if (index != -1) return index;
    return binarySearch(mountainArr, peak, n - 1, target, 0);
}

int main() {
    // Test cases
    int arr1[] = {1, 2, 3, 4, 5, 3, 1};
    MountainArray mountainArr1 = {arr1, sizeof(arr1) / sizeof(arr1[0])};
    printf("%d\n", findInMountainArray(3, &mountainArr1));  // Output: 2

    int arr2[] = {0, 1, 2, 4, 2, 1};
    MountainArray mountainArr2 = {arr2, sizeof(arr2) / sizeof(arr2[0])};
    printf("%d\n", findInMountainArray(3, &mountainArr2));  // Output: -1

    return 0;
}