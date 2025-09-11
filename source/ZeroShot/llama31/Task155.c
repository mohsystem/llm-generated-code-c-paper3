#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Heap sort
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
    int arr2[] = {1, 2, 3, 4, 5};
    int arr3[] = {5, 4, 3, 2, 1};
    int arr4[] = {1, 1, 1, 1, 1};
    int arr5[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    heapSort(arr1, sizeof(arr1) / sizeof(arr1[0]));
    heapSort(arr2, sizeof(arr2) / sizeof(arr2[0]));
    heapSort(arr3, sizeof(arr3) / sizeof(arr3[0]));
    heapSort(arr4, sizeof(arr4) / sizeof(arr4[0]));
    heapSort(arr5, sizeof(arr5) / sizeof(arr5[0]));

    printArray(arr1, sizeof(arr1) / sizeof(arr1[0]));
    printArray(arr2, sizeof(arr2) / sizeof(arr2[0]));
    printArray(arr3, sizeof(arr3) / sizeof(arr3[0]));
    printArray(arr4, sizeof(arr4) / sizeof(arr4[0]));
    printArray(arr5, sizeof(arr5) / sizeof(arr5[0]));

    return 0;
}