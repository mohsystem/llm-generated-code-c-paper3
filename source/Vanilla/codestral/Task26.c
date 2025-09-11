#include <stdio.h>

int findIt(int arr[], int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result ^= arr[i];
    }
    return result;
}

int main() {
    int arr1[] = {7};
    int arr2[] = {0};
    int arr3[] = {1,1,2};
    int arr4[] = {0,1,0,1,0};
    int arr5[] = {1,2,2,3,3,3,4,3,3,3,2,2,1};
    printf("%d\n", findIt(arr1, 1));
    printf("%d\n", findIt(arr2, 1));
    printf("%d\n", findIt(arr3, 3));
    printf("%d\n", findIt(arr4, 5));
    printf("%d\n", findIt(arr5, 13));
    return 0;
}