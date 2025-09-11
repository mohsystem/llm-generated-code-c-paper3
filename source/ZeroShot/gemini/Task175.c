#include <stdio.h>
#include <stdlib.h>

// Define the MountainArray interface (mimicking the provided interface)
typedef struct {
    int (*get)(int index, void *context);
    int (*length)(void *context);
    void *context;
} MountainArray;


int get_mountain_arr(int index, void *context) {
    return ((int *)context)[index];
}

int length_mountain_arr(void *context) {
    int *arr = (int *)context;
    int count = 0;
    while (*arr) {
        count++;
        arr++;
    }

    return count;
}


int findPeakIndex(MountainArray *mountainArr) {
    int left = 0;
    int right = mountainArr->length(mountainArr->context) - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (mountainArr->get(mid, mountainArr->context) < mountainArr->get(mid + 1, mountainArr->context)) {
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
        int val = mountainArr->get(mid, mountainArr->context);

        if (val == target) {
            return mid;
        } else if (val < target) {
            if (ascending) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        } else {
            if (ascending) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
    }
    return -1;
}


int findInMountainArray(int target, MountainArray *mountainArr) {
    int peakIndex = findPeakIndex(mountainArr);
    int leftIndex = binarySearch(mountainArr, target, 0, peakIndex, 1);
    if (leftIndex != -1) {
        return leftIndex;
    }
    return binarySearch(mountainArr, target, peakIndex + 1, mountainArr->length(mountainArr->context) - 1, 0);
}




int main() {
     int arr1[] = {1, 2, 3, 4, 5, 3, 1, 0};
    MountainArray mountainArr1;
    mountainArr1.get = get_mountain_arr;
    mountainArr1.length = length_mountain_arr;
    mountainArr1.context = arr1;
    printf("%d\n", findInMountainArray(3, &mountainArr1)); // Output: 2

     int arr2[] = {0, 1, 2, 4, 2, 1, 0};
    MountainArray mountainArr2;
    mountainArr2.get = get_mountain_arr;
    mountainArr2.length = length_mountain_arr;
    mountainArr2.context = arr2;
    printf("%d\n", findInMountainArray(3, &mountainArr2)); // Output: -1

     int arr3[] = {0, 5, 3, 1, 0};
    MountainArray mountainArr3;
    mountainArr3.get = get_mountain_arr;
    mountainArr3.length = length_mountain_arr;
    mountainArr3.context = arr3;
    printf("%d\n", findInMountainArray(1, &mountainArr3)); // Output: 3

    int arr4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    MountainArray mountainArr4;
    mountainArr4.get = get_mountain_arr;
    mountainArr4.length = length_mountain_arr;
    mountainArr4.context = arr4;
    printf("%d\n", findInMountainArray(10, &mountainArr4)); // Output: 9

     int arr5[] = {1, 2, 3, 4, 5, 4, 3, 2, 1, 0};
    MountainArray mountainArr5;
    mountainArr5.get = get_mountain_arr;
    mountainArr5.length = length_mountain_arr;
    mountainArr5.context = arr5;
    printf("%d\n", findInMountainArray(0, &mountainArr5)); // Output: -1


    return 0;
}