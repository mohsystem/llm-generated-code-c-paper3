#include <stdio.h>
#include <stdlib.h>

int findOdd(int arr[], int n) {
    int counts[10000] = {0}; // Assuming the range of numbers is within 10000
    for (int i = 0; i < n; i++) {
        ++counts[arr[i]];
    }
    for (int i = 0; i < 10000; i++) {
        if (counts[i] % 2 != 0) {
            return i;
        }
    }
    return -1;  // Should never reach here
}

int main() {
    int arr1[] = {7};
    printf("%d\n", findOdd(arr1, 1));  // 7
    int arr2[] = {0};
    printf("%d\n", findOdd(arr2, 1));  // 0
    int arr3[] = {1, 1, 2};
    printf("%d\n", findOdd(arr3, 3));  // 2
    int arr4[] = {0, 1, 0, 1, 0};
    printf("%d\n", findOdd(arr4, 5));  // 0
    int arr5[] = {1, 2, 2, 3, 3, 3, 4, 3, 3, 3, 2, 2, 1};
    printf("%d\n", findOdd(arr5, 13));  // 4
    return 0;
}