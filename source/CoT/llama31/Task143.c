#include <stdio.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    // Test cases
    int testCases[][7] = {
        {5, 1, 4, 2, 8},
        {64, 34, 25, 12, 22, 11, 90},
        {-2, 45, 0, 11, -9},
        {20, 12, 10, 15, 2},
        {1, 3, 5, 7, 9}
    };
    int sizes[] = {5, 7, 5, 5, 5};

    for (int i = 0; i < 5; i++) {
        bubbleSort(testCases[i], sizes[i]);
        printf("Sorted array: ");
        printArray(testCases[i], sizes[i]);
    }

    return 0;
}