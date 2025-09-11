#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void posNegSort(int arr[], int n) {
    int positiveNumbers[n];
    int positiveCount = 0;

    // Separate positive numbers
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            positiveNumbers[positiveCount++] = arr[i];
        }
    }

    // Sort positive numbers
    for (int i = 0; i < positiveCount - 1; i++) {
        for (int j = i + 1; j < positiveCount; j++) {
            if (positiveNumbers[i] > positiveNumbers[j]) {
                swap(&positiveNumbers[i], &positiveNumbers[j]);
            }
        }
    }

    // Reconstruct the array
    int posIndex = 0;
    int negIndex = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            arr[i] = positiveNumbers[posIndex++];
        } else {
            while (negIndex < n && arr[negIndex] > 0) {
                negIndex++;
            }
            int temp = arr[i];
            arr[i] = arr[negIndex];
            arr[negIndex] = temp;
            negIndex++;
        }
    }
}

int main() {
    int testCases[][7] = {
        {6, 3, -2, 5, -8, 2, -2},
        {6, 5, 4, -1, 3, 2, -1, 1},
        {-5, -5, -5, -5, 7, -5},
        {}
    };

    int lengths[] = {7, 8, 6, 0};

    for (int i = 0; i < 4; i++) {
        posNegSort(testCases[i], lengths[i]);
        for (int j = 0; j < lengths[i]; j++) {
            printf("%d ", testCases[i][j]);
        }
        printf("\n");
    }

    return 0;
}