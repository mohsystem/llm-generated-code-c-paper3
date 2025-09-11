#include <stdio.h>

int longestRun(int arr[], int n) {
    if (n == 0) return 0;

    int maxLen = 1;
    int currentLen = 1;

    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1] + 1 || arr[i] == arr[i - 1] - 1) {
            currentLen++;
            if (currentLen > maxLen) maxLen = currentLen;
        } else {
            currentLen = 1;
        }
    }
    return maxLen;
}

int main() {
    int arr1[] = {1, 2, 3, 10, 11, 15};
    int arr2[] = {5, 4, 2, 1};
    int arr3[] = {3, 5, 7, 10, 15};
    int arr4[] = {1, 2, 3, 5, 6, 7, 8, 9};
    int arr5[] = {10, 9, 8, 7, 3, 2, 1};

    printf("%d\n", longestRun(arr1, 6)); // ➞ 3
    printf("%d\n", longestRun(arr2, 4)); // ➞ 2
    printf("%d\n", longestRun(arr3, 5)); // ➞ 1
    printf("%d\n", longestRun(arr4, 8)); // ➞ 5
    printf("%d\n", longestRun(arr5, 7)); // ➞ 4

    return 0;
}