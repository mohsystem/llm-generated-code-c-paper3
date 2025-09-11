
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* arr;
    int length;
} MountainArray;

int get(MountainArray* obj, int index) {
    return obj->arr[index];
}

int mountainArrayLength(MountainArray* obj) {
    return obj->length;
}

int findInMountainArray(int target, MountainArray* mountainArr) {
    int n = mountainArrayLength(mountainArr);
    
    // Find peak element
    int left = 1;
    int right = n - 2;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (get(mountainArr, mid) < get(mountainArr, mid + 1)) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    int peak = left;
    
    // Search in left side
    left = 0;
    right = peak;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int midVal = get(mountainArr, mid);
        if (midVal == target) {
            return mid;
        } else if (midVal < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    // Search in right side
    left = peak;
    right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int midVal = get(mountainArr, mid);
        if (midVal == target) {
            return mid;
        } else if (midVal > target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

int main() {
    // Test cases
    int test_arrays[][7] = {
        {1, 2, 3, 4, 5, 3, 1},
        {0, 1, 2, 4, 2, 1},
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {1, 3, 5, 7, 6, 4, 2}
    };
    int lengths[] = {7, 6, 5, 5, 7};
    int targets[] = {3, 3, 3, 3, 7};
    
    for (int i = 0; i < 5; i++) {
        MountainArray mountainArr = {test_arrays[i], lengths[i]};
        printf("Test case %d: %d\\n", i + 1, findInMountainArray(targets[i], &mountainArr));
    }
    
    return 0;
}
