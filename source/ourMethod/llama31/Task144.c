#include <stdio.h>
#include <stdlib.h>

void mergeArrays(int arr1[], int arr2[], int n1, int n2, int result[]) {
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2) {
        if (arr1[i] < arr2[j]) {
            result[k++] = arr1[i++];
        } else {
            result[k++] = arr2[j++];
        }
    }
    // Copy remaining elements of arr1, if any
    while (i < n1) {
        result[k++] = arr1[i++];
    }
    // Copy remaining elements of arr2, if any
    while (j < n2) {
        result[k++] = arr2[j++];
    }
}

int main() {
    int arr1[] = {11, 15, 17};
    int arr2[] = {2, 5, 8};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int result[n1 + n2];
    mergeArrays(arr1, arr2, n1, n2, result);
    for (int i = 0; i < n1 + n2; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // Test cases
    int arr3[] = {1, 3, 5};
    int arr4[] = {2, 4, 6};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    int result2[n3 + n4];
    mergeArrays(arr3, arr4, n3, n4, result2);
    for (int i = 0; i < n3 + n4; i++) {
        printf("%d ", result2[i]);
    }
    printf("\n");

    int arr5[] = {10, 20, 30};
    int arr6[] = {5, 15, 25};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    int n6 = sizeof(arr6) / sizeof(arr6[0]);
    int result3[n5 + n6];
    mergeArrays(arr5, arr6, n5, n6, result3);
    for (int i = 0; i < n5 + n6; i++) {
        printf("%d ", result3[i]);
    }
    printf("\n");

    int arr7[] = {1, 3};
    int arr8[] = {2, 4, 6};
    int n7 = sizeof(arr7) / sizeof(arr7[0]);
    int n8 = sizeof(arr8) / sizeof(arr8[0]);
    int result4[n7 + n8];
    mergeArrays(arr7, arr8, n7, n8, result4);
    for (int i = 0; i < n7 + n8; i++) {
        printf("%d ", result4[i]);
    }
    printf("\n");

    int arr9[] = {1, 3, 5};
    int arr10[] = {2};
    int n9 = sizeof(arr9) / sizeof(arr9[0]);
    int n10 = sizeof(arr10) / sizeof(arr10[0]);
    int result5[n9 + n10];
    mergeArrays(arr9, arr10, n9, n10, result5);
    for (int i = 0; i < n9 + n10; i++) {
        printf("%d ", result5[i]);
    }
    printf("\n");

    return 0;
}