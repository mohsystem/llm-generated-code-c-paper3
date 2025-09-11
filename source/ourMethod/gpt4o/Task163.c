#include <stdio.h>

int longestRun(int arr[], int size) {
    if (size == 0) return 0;
    
    int maxRun = 1;
    int currentRun = 1;

    for (int i = 1; i < size; i++) {
        if (arr[i] == arr[i - 1] + 1 || arr[i] == arr[i - 1] - 1) {
            currentRun++;
        } else {
            if (currentRun > maxRun) {
                maxRun = currentRun;
            }
            currentRun = 1;
        }
    }
    if (currentRun > maxRun) {
        maxRun = currentRun;
    }
    return maxRun;
}

int main() {
    int arr1[] = {1, 2, 3, 5, 6, 7, 8, 9};
    int arr2[] = {1, 2, 3, 10, 11, 15};
    int arr3[] = {5, 4, 2, 1};
    int arr4[] = {3, 5, 7, 10, 15};
    int arr5[] = {10, 9, 8, 7, 6};

    printf("%d\n", longestRun(arr1, sizeof(arr1)/sizeof(arr1[0]))); // ➞ 5
    printf("%d\n", longestRun(arr2, sizeof(arr2)/sizeof(arr2[0]))); // ➞ 3
    printf("%d\n", longestRun(arr3, sizeof(arr3)/sizeof(arr3[0]))); // ➞ 2
    printf("%d\n", longestRun(arr4, sizeof(arr4)/sizeof(arr4[0]))); // ➞ 1
    printf("%d\n", longestRun(arr5, sizeof(arr5)/sizeof(arr5[0]))); // ➞ 5

    return 0;
}