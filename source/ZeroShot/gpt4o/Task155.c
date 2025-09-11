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

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int testCases[5][5] = {
        {4, 10, 3, 5, 1},
        {1, 3, 5, 7, 9},
        {9, 7, 5, 3, 1},
        {5, 12, 11, 13, 6},
        {2, 4, 1, 3, 5}
    };

    int sizes[] = {5, 5, 5, 5, 5};

    for (int i = 0; i < 5; i++) {
        heapSort(testCases[i], sizes[i]);
        printArray(testCases[i], sizes[i]);
    }

    return 0;
}