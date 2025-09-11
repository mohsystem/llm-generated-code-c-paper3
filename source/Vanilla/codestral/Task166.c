#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void posNegSort(int arr[], int n) {
    int pos[n], posIndex = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            pos[posIndex++] = arr[i];
        }
    }
    for (int i = 0; i < posIndex - 1; i++) {
        for (int j = 0; j < posIndex - i - 1; j++) {
            if (pos[j] > pos[j + 1]) {
                swap(&pos[j], &pos[j + 1]);
            }
        }
    }
    posIndex = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            arr[i] = pos[posIndex++];
        }
    }
}

int main() {
    int arr1[] = {6, 3, -2, 5, -8, 2, -2};
    int arr2[] = {6, 5, 4, -1, 3, 2, -1, 1};
    int arr3[] = {-5, -5, -5, -5, 7, -5};
    int arr4[] = {};

    posNegSort(arr1, sizeof(arr1)/sizeof(arr1[0]));
    posNegSort(arr2, sizeof(arr2)/sizeof(arr2[0]));
    posNegSort(arr3, sizeof(arr3)/sizeof(arr3[0]));
    posNegSort(arr4, sizeof(arr4)/sizeof(arr4[0]));

    for (int i = 0; i < sizeof(arr1)/sizeof(arr1[0]); i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");
    for (int i = 0; i < sizeof(arr2)/sizeof(arr2[0]); i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");
    for (int i = 0; i < sizeof(arr3)/sizeof(arr3[0]); i++) {
        printf("%d ", arr3[i]);
    }
    printf("\n");
    for (int i = 0; i < sizeof(arr4)/sizeof(arr4[0]); i++) {
        printf("%d ", arr4[i]);
    }
    printf("\n");

    return 0;
}