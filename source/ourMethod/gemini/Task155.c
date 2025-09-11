#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    int arr1[] = {12, 11, 13, 5, 6, 7};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    heapSort(arr1, n1);
    for (int i = 0; i < n1; i++)
        printf("%d ", arr1[i]);
    printf("\n");

    int arr2[] = {5, 1, 4, 2, 8};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    heapSort(arr2, n2);
    for (int i = 0; i < n2; i++)
        printf("%d ", arr2[i]);
    printf("\n");

    int arr3[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    heapSort(arr3, n3);
    for (int i = 0; i < n3; i++)
        printf("%d ", arr3[i]);
    printf("\n");

    int arr4[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    heapSort(arr4, n4);
    for (int i = 0; i < n4; i++)
        printf("%d ", arr4[i]);
    printf("\n");

    int arr5[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    heapSort(arr5, n5);
    for (int i = 0; i < n5; i++)
        printf("%d ", arr5[i]);
    printf("\n");


    return 0;
}