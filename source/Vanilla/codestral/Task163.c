#include <stdio.h>
#include <stdlib.h>

int longestRun(int nums[], int size) {
    if (size == 0) return 0;

    int maxLen = 1;
    int currLen = 1;

    for (int i = 1; i < size; i++) {
        if (nums[i] == nums[i - 1] + 1 || nums[i] == nums[i - 1] - 1) {
            currLen++;
        } else {
            maxLen = (currLen > maxLen) ? currLen : maxLen;
            currLen = 1;
        }
    }

    return (currLen > maxLen) ? currLen : maxLen;
}

int main() {
    int arr1[] = {1, 2, 3, 5, 6, 7, 8, 9};
    int arr2[] = {1, 2, 3, 10, 11, 15};
    int arr3[] = {5, 4, 2, 1};
    int arr4[] = {3, 5, 7, 10, 15};
    int arr5[] = {};

    printf("%d\n", longestRun(arr1, sizeof(arr1)/sizeof(arr1[0])));  // 5
    printf("%d\n", longestRun(arr2, sizeof(arr2)/sizeof(arr2[0])));  // 3
    printf("%d\n", longestRun(arr3, sizeof(arr3)/sizeof(arr3[0])));  // 2
    printf("%d\n", longestRun(arr4, sizeof(arr4)/sizeof(arr4[0])));  // 1
    printf("%d\n", longestRun(arr5, sizeof(arr5)/sizeof(arr5[0])));  // 0

    return 0;
}