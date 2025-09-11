#include <stdio.h>

typedef struct {
    int* arr;
    int (*get)(int index);
    int (*length)();
} MountainArray;

MountainArray* MountainArray_create(int* arr, int len) {
    MountainArray* obj = malloc(sizeof(MountainArray));
    obj->arr = arr;
    obj->get = &get;
    obj->length = &length;
    return obj;
}

int get(int index) {
    return this->arr[index];
}

int length() {
    return sizeof(this->arr) / sizeof(this->arr[0]);
}

int findPeak(MountainArray* mountainArr) {
    int left = 0, right = mountainArr->length() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (mountainArr->get(mid) < mountainArr->get(mid + 1)) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int binarySearch(MountainArray* mountainArr, int left, int right, int target) {
    int asc = mountainArr->get(left) < mountainArr->get(right);
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (mountainArr->get(mid) == target) {
            return mid;
        }
        if (asc) {
            if (mountainArr->get(mid) < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        } else {
            if (mountainArr->get(mid) > target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return -1;
}

int findInMountainArray(int target, MountainArray* mountainArr) {
    int peak = findPeak(mountainArr);
    int left = binarySearch(mountainArr, 0, peak, target);
    if (left != -1) {
        return left;
    }
    return binarySearch(mountainArr, peak + 1, mountainArr->length() - 1, target);
}

int main() {
    int arr1[] = {1,2,3,4,5,3,1};
    MountainArray* mountainArr1 = MountainArray_create(arr1, sizeof(arr1)/sizeof(arr1[0]));
    printf("%d\n", findInMountainArray(3, mountainArr1));
    int arr2[] = {0,1,2,4,2,1};
    MountainArray* mountainArr2 = MountainArray_create(arr2, sizeof(arr2)/sizeof(arr2[0]));
    printf("%d\n", findInMountainArray(3, mountainArr2));
    return 0;
}