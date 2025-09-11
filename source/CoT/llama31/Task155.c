#include <stdio.h>

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    // Build heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements one by one
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr1[] = {12, 11, 31, 3, 5, 7, 9};
    int arr2[] = {4, 10, 3, 8, 1};
    int arr3[] = {20, 12, 10, 3, 4};
    int arr4[] = {5, 2, 8, 1, 9};
    int arr5[] = {6, 3, 1, 8, 4, 2};

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

    printf("Sorted array 1: ");
    printArray(arr1, n1);
    printf("Sorted array 2: ");
    printArray(arr2, n2);
    printf("Sorted array 3: ");
    printArray(arr3, n3);
    printf("Sorted array 4: ");
    printArray(arr4, n4);
    printf("Sorted array 5: ");
    printArray(arr5, n5);

    return 0;
}