#include <stdio.h>

int findIndex(int arr[], int size) {
    int totalSum = 0;
    int leftSum = 0;
    for (int i = 0; i < size; i++) totalSum += arr[i];
    for (int i = 0; i < size; i++) {
        if (leftSum == totalSum - leftSum - arr[i]) return i;
        leftSum += arr[i];
    }
    return -1;
}

int main() {
    int arr1[] = {1,2,3,4,3,2,1};
    int arr2[] = {1,100,50,-51,1,1};
    int arr3[] = {20,10,-80,10,10,15,35};
    printf("%d\n", findIndex(arr1, sizeof(arr1)/sizeof(arr1[0])));  // prints 3
    printf("%d\n", findIndex(arr2, sizeof(arr2)/sizeof(arr2[0])));  // prints 1
    printf("%d\n", findIndex(arr3, sizeof(arr3)/sizeof(arr3[0])));  // prints 0
    return 0;
}