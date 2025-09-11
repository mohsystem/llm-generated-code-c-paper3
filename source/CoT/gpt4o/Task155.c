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
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int testCases[5][6] = {
        {12, 11, 13, 5, 6, 7},
        {4, 10, 3, 5, 1, 0},
        {1, 3, 9, 4, 2, 0},
        {10, 15, 20, 5, 25, 0},
        {3, 6, 9, 12, 15, 0}
    };

    int sizes[5] = {6, 5, 5, 5, 5};

    for (int i = 0; i < 5; i++) {
        heapSort(testCases[i], sizes[i]);
        printArray(testCases[i], sizes[i]);
    }

    return 0;
}