#include <stdio.h>
#include <stdlib.h>

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int longestRun(int arr[], int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    qsort(arr, n, sizeof(int), cmpfunc);

    int longest = 1;
    int currentRun = 1;

    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1] + 1) {
            currentRun++;
        } else if (arr[i] != arr[i - 1]) {
            if (currentRun > longest) {
                longest = currentRun;
            }
            currentRun = 1;
        }
    }
    if (currentRun > longest) {
        longest = currentRun;
    }
    return longest;
}

int main() {
    int arr1[] = {1, 2, 3, 5, 6, 7, 8, 9};
    printf("%d\n", longestRun(arr1, 8)); // 5

    int arr2[] = {1, 2, 3, 10, 11, 15};
    printf("%d\n", longestRun(arr2, 6)); // 3

    int arr3[] = {5, 4, 2, 1};
    printf("%d\n", longestRun(arr3, 4)); // 2

    int arr4[] = {3, 5, 7, 10, 15};
    printf("%d\n", longestRun(arr4, 5)); // 1

    int arr5[] = {1, 2, 3, 4, 5};
    printf("%d\n", longestRun(arr5, 5)); // 5

    return 0;
}