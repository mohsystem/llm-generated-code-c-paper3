#include <stdio.h>

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        int swap = arr[i];
        arr[i] = arr[largest];
        arr[largest] = swap;

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int testCases[][6] = {
        {12, 11, 13, 5, 6, 7},
        {4, 10, 3, 5, 1},
        {1, 2, 3, 4, 5},
        {9, 8, 7, 6, 5},
        {0, -1, 3, -10, 5}
    };
    int sizes[] = {6, 5, 5, 5, 5};

    for (int i = 0; i < 5; i++) {
        heapSort(testCases[i], sizes[i]);
        printArray(testCases[i], sizes[i]);
    }

    return 0;
}