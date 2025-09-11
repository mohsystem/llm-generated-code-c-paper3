#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void posNegSort(int arr[], int n) {
    int* positives = (int*)malloc(n * sizeof(int));
    int posCount = 0;
    int* negatives = (int*)malloc(n * sizeof(int));
    int negCount = 0;

    // Separate positive and negative numbers
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            positives[posCount++] = arr[i];
        } else {
            negatives[negCount++] = arr[i];
        }
    }

    // Sort the positive numbers
    sort(positives, posCount);

    // Combine the sorted positives and negatives
    int j = 0, k = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            arr[i] = positives[j++];
        } else {
            arr[i] = negatives[k++];
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

    int sizes[] = {7, 8, 6, 0};

    for (int i = 0; i < 4; i++) {
        posNegSort(testCases[i], sizes[i]);
        for (int j = 0; j < sizes[i]; j++) {
            printf("%d ", testCases[i][j]);
        }
        printf("\n");
    }

    return 0;
}