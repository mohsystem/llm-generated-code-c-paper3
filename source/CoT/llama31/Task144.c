#include <stdio.h>

void mergeArrays(int arr1[], int arr2[], int m, int n, int arr3[]) {
    int i = 0, j = 0, k = 0;
    while (i < m && j < n) {
        if (arr1[i] < arr2[j]) {
            arr3[k++] = arr1[i++];
        } else {
            arr3[k++] = arr2[j++];
        }
    }
    // Copy remaining elements of arr1, if any
    while (i < m) {
        arr3[k++] = arr1[i++];
    }
    // Copy remaining elements of arr2, if any
    while (j < n) {
        arr3[k++] = arr2[j++];
    }
}

int main() {
    // Test case 1
    int arr1[] = {1, 3, 5, 7};
    int arr2[] = {2, 4, 6, 8};
    int m = sizeof(arr1) / sizeof(arr1[0]);
    int n = sizeof(arr2) / sizeof(arr2[0]);
    int arr3[m + n];
    mergeArrays(arr1, arr2, m, n, arr3);
    for (int i = 0; i < m + n; i++) {
        printf("%d ", arr3[i]);
    }
    printf("\n");

    // Test case 2
    int arr4[] = {5, 8, 9};
    int arr5[] = {4, 7, 8};
    m = sizeof(arr4) / sizeof(arr4[0]);
    n = sizeof(arr5) / sizeof(arr5[0]);
    int arr6[m + n];
    mergeArrays(arr4, arr5, m, n, arr6);
    for (int i = 0; i < m + n; i++) {
        printf("%d ", arr6[i]);
    }
    printf("\n");

    // Test case 3
    int arr7[] = {1, 3};
    int arr8[] = {2, 4, 6};
    m = sizeof(arr7) / sizeof(arr7[0]);
    n = sizeof(arr8) / sizeof(arr8[0]);
    int arr9[m + n];
    mergeArrays(arr7, arr8, m, n, arr9);
    for (int i = 0; i < m + n; i++) {
        printf("%d ", arr9[i]);
    }
    printf("\n");

    // Test case 4
    int arr10[] = {1, 3, 5};
    int arr11[] = {};
    m = sizeof(arr10) / sizeof(arr10[0]);
    n = sizeof(arr11) / sizeof(arr11[0]);
    int arr12[m + n];
    mergeArrays(arr10, arr11, m, n, arr12);
    for (int i = 0; i < m + n; i++) {
        printf("%d ", arr12[i]);
    }
    printf("\n");

    // Test case 5
    int arr13[] = {};
    int arr14[] = {2, 4, 6};
    m = sizeof(arr13) / sizeof(arr13[0]);
    n = sizeof(arr14) / sizeof(arr14[0]);
    int arr15[m + n];
    mergeArrays(arr13, arr14, m, n, arr15);
    for (int i = 0; i < m + n; i++) {
        printf("%d ", arr15[i]);
    }
    printf("\n");

    return 0;
}