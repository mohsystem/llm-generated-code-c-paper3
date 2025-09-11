#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

int main() {
    int testCase1[] = {5, 3, 8, 1, 2};
    int n1 = sizeof(testCase1) / sizeof(testCase1[0]);
    bubbleSort(testCase1, n1);
    for (int i = 0; i < n1; i++) {
        printf("%d ", testCase1[i]);
    }
    printf("\n");

    int testCase2[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n2 = sizeof(testCase2) / sizeof(testCase2[0]);
    bubbleSort(testCase2, n2);
    for (int i = 0; i < n2; i++) {
        printf("%d ", testCase2[i]);
    }
    printf("\n");

    int testCase3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(testCase3) / sizeof(testCase3[0]);
    bubbleSort(testCase3, n3);
    for (int i = 0; i < n3; i++) {
        printf("%d ", testCase3[i]);
    }
    printf("\n");

    int testCase4[] = {5, 5, 5, 5, 5};
    int n4 = sizeof(testCase4) / sizeof(testCase4[0]);
    bubbleSort(testCase4, n4);
    for (int i = 0; i < n4; i++) {
        printf("%d ", testCase4[i]);
    }
    printf("\n");

    int testCase5[] = {};
    int n5 = sizeof(testCase5) / sizeof(testCase5[0]);
    bubbleSort(testCase5, n5);
    for (int i = 0; i < n5; i++) {
        printf("%d ", testCase5[i]);
    }

    return 0;
}