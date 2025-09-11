#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void posNegSort(int arr[], int length) {
    int *positives = (int *)malloc(length * sizeof(int));
    int posCount = 0;

    for (int i = 0; i < length; i++) {
        if (arr[i] > 0) {
            positives[posCount++] = arr[i];
        }
    }

    qsort(positives, posCount, sizeof(int), compare);

    int posIndex = 0;
    for (int i = 0; i < length; i++) {
        if (arr[i] > 0) {
            arr[i] = positives[posIndex++];
        }
    }

    free(positives);
}

void printArray(int arr[], int length) {
    printf("[");
    for (int i = 0; i < length; i++) {
        printf("%d", arr[i]);
        if (i < length - 1) printf(", ");
    }
    printf("]\n");
}

int main() {
    int arr1[] = {6, 3, -2, 5, -8, 2, -2};
    int arr2[] = {6, 5, 4, -1, 3, 2, -1, 1};
    int arr3[] = {-5, -5, -5, -5, 7, -5};
    int arr4[] = {};
    int arr5[] = {3, -3, 1, 0, -1, 2, 4, -4, 5};

    posNegSort(arr1, 7);
    posNegSort(arr2, 8);
    posNegSort(arr3, 6);
    posNegSort(arr4, 0);
    posNegSort(arr5, 9);

    printArray(arr1, 7);  // [2, 3, -2, 5, -8, 6, -2]
    printArray(arr2, 8);  // [1, 2, 3, -1, 4, 5, -1, 6]
    printArray(arr3, 6);  // [-5, -5, -5, -5, 7, -5]
    printArray(arr4, 0);  // []
    printArray(arr5, 9);  // [1, -3, 2, 0, -1, 3, 4, -4, 5]

    return 0;
}