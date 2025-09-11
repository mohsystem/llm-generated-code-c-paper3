
// Note: C implementation would be complex due to lack of classes and objects.
// Here's a simplified version without the MountainArray class implementation.

#include <stdio.h>

int findPeak(int arr[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < arr[mid + 1])
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

int binarySearch(int arr[], int left, int right, int target, int ascending) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        if (ascending) {
            if (arr[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        } else {
            if (arr[mid] < target)
                right = mid - 1;
            else
                left = mid + 1;
        }
    }
    return -1;
}

int findInMountainArray(int target, int arr[], int n) {
    int peak = findPeak(arr, n);
    int leftResult = binarySearch(arr, 0, peak, target, 1);
    if (leftResult != -1)
        return leftResult;
    return binarySearch(arr, peak, n-1, target, 0);
}

int main() {
    int arrays[][7] = {
        {1,2,3,4,5,3,1},
        {0,1,2,4,2,1,0},
        {1,3,5,7,6,4,2},
        {1,2,3,4,5,3,1},
        {1,5,2,1,1,1,1}
    };
    int targets[] = {3, 3, 7, 3, 2};
    int sizes[] = {7, 7, 7, 7, 7};
    
    for (int i = 0; i < 5; i++) {
        printf("Test case %d: %d\\n", i+1, 
            findInMountainArray(targets[i], arrays[i], sizes[i]));
    }
    return 0;
}
