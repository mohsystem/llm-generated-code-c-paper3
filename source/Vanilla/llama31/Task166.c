#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sortArray(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[i] > arr[j]) {
                swap(&arr[i], &arr[j]);
            }
        }
    }
}

int* posNegSort(int arr[], int n) {
    int* positives = (int*)malloc(n * sizeof(int));
    int positiveCount = 0;

    // Store all positive numbers
    for (int i = 0; i < n; ++i) {
        if (arr[i] > 0) {
            positives[positiveCount++] = arr[i];
        }
    }

    // Sort the positive numbers
    sortArray(positives, positiveCount);

    int j = 0;
    int* sorted = (int*)malloc(n * sizeof(int));

    // Replace positive numbers with sorted positives
    for (int i = 0; i < n; ++i) {
        if (arr[i] > 0) {
            sorted[i] = positives[j++];
        } else {
            sorted[i] = arr[i];
        }
    }

    free(positives);
    return sorted;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int testCases[][7] = {
        {6, 3, -2, 5, -8, 2, -2},
        {6, 5, 4, -1, 3, 2, -1, 1},
        {-5, -5, -5, -5, 7, -5},
        {}
    };

    int sizes[] = {7, 8, 6, 0};

    for (int i = 0; i < 4; ++i) {
        int* testCase = testCases[i];
        int size = sizes[i];
        int* result = posNegSort(testCase, size);

        printArray(result, size);
        free(result);
    }

    return 0;
}