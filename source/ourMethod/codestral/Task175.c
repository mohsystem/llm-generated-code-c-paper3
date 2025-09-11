// Task175
#include <stdio.h>

typedef struct {
    int* arr;
    int length;
} MountainArray;

int get(MountainArray* obj, int index) {
    return obj->arr[index];
}

int length(MountainArray* obj) {
    return obj->length;
}

int findInMountainArray(int target, MountainArray* mountainArr) {
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
    int peak = left;
    left = 0;
    right = peak;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (get(mountainArr, mid) == target) {
            return mid;
        } else if (get(mountainArr, mid) < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    left = peak;
    right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (get(mountainArr, mid) == target) {
            return mid;
        } else if (get(mountainArr, mid) > target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    int arr1[] = {1,2,3,4,5,3,1};
    MountainArray mountainArr1 = {arr1, sizeof(arr1)/sizeof(arr1[0])};
    printf("%d\n", findInMountainArray(3, &mountainArr1)); // Output: 2

    int arr2[] = {0,1,2,4,2,1};
    MountainArray mountainArr2 = {arr2, sizeof(arr2)/sizeof(arr2[0])};
    printf("%d\n", findInMountainArray(3, &mountainArr2)); // Output: -1

    return 0;
}