#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
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
    // Build heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements one by one
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr1[] = {9, 4, 3, 8, 10, 2, 5};
    int arr2[] = {1, 3, 5, 7, 9};
    int arr3[] = {9, 8, 7, 6, 5};
    int arr4[] = {1, 2, 3, 4, 5};
    int arr5[] = {5, 4, 3, 2, 1};

    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    int n5 = sizeof(arr5) / sizeof(arr5[0]);

    heapSort(arr1, n1);
    heapSort(arr2, n2);
    heapSort(arr3, n3);
    heapSort(arr4, n4);
    heapSort(arr5, n5);

    printArray(arr1, n1);
    printArray(arr2, n2);
    printArray(arr3, n3);
    printArray(arr4, n4);
    printArray(arr5, n5);

    return 0;
}