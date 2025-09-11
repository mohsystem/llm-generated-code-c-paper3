#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void posNegSort(int arr[], int n) {
    int positiveNumbers[n];
    int posIndex = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            positiveNumbers[posIndex++] = arr[i];
        }
    }
    bubbleSort(positiveNumbers, posIndex);
    posIndex = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            arr[i] = positiveNumbers[posIndex++];
        }
    }
}

int main() {
    int arr1[] = {6, 3, -2, 5, -8, 2, -2};
    int arr2[] = {6, 5, 4, -1, 3, 2, -1, 1};
    int arr3[] = {-5, -5, -5, -5, 7, -5};
    int arr4[] = {};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int n4 = sizeof(arr4) / sizeof(arr4[0]);

    posNegSort(arr1, n1);
    posNegSort(arr2, n2);
    posNegSort(arr3, n3);
    posNegSort(arr4, n4);

    for (int i = 0; i < n1; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    for (int i = 0; i < n2; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    for (int i = 0; i < n3; i++) {
        printf("%d ", arr3[i]);
    }
    printf("\n");

    for (int i = 0; i < n4; i++) {
        printf("%d ", arr4[i]);
    }
    printf("\n");

    return 0;
}