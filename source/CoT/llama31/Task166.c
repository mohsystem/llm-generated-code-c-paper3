#include <stdio.h>
#include <stdlib.h>

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to partition the array for quicksort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Function to implement quicksort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to sort positive numbers and keep negative numbers untouched
void posNegSort(int* arr, int n) {
    int* positives = (int*)malloc(n * sizeof(int));
    int* negatives = (int*)malloc(n * sizeof(int));
    int posIndex = 0, negIndex = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            positives[posIndex++] = arr[i];
        } else {
            negatives[negIndex++] = arr[i];
        }
    }

    // Sort the positive numbers
    quickSort(positives, 0, posIndex - 1);

    // Combine the sorted positives and negatives
    int i = 0, j = 0, k = 0;
    while (i < posIndex || j < negIndex) {
        if (i < posIndex && (j == negIndex || positives[i] <= negatives[j])) {
            arr[k++] = positives[i++];
        } else {
            arr[k++] = negatives[j++];
        }
    }

    free(positives);
    free(negatives);
}

int main() {
    int testCases[][7] = {
        {6, 3, -2, 5, -8, 2, -2},
        {6, 5, 4, -1, 3, 2, -1, 1},
        {-5, -5, -5, -5, 7, -5},
        {}
    };

    for (int i = 0; i < sizeof(testCases) / sizeof(testCases[0]); i++) {
        int size = sizeof(testCases[i]) / sizeof(testCases[i][0]);
        if (size == 1 && testCases[i][0] == 0) break; // Empty array
        posNegSort(testCases[i], size);
        for (int j = 0; j < size; j++) {
            printf("%d ", testCases[i][j]);
        }
        printf("\n");
    }

    return 0;
}