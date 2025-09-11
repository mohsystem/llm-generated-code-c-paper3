#include <stdio.h>
#include <stdlib.h>

int* posNegSort(int* arr, int size) {
    int* positives = (int*)malloc(size * sizeof(int));
    int posCount = 0;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            positives[posCount++] = arr[i];
        }
    }
    
    for (int i = 0; i < posCount - 1; i++) {
        for (int j = i + 1; j < posCount; j++) {
            if (positives[i] > positives[j]) {
                int temp = positives[i];
                positives[i] = positives[j];
                positives[j] = temp;
            }
        }
    }
    
    int posIndex = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            arr[i] = positives[posIndex++];
        }
    }
    
    free(positives);
    return arr;
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr1[] = {6, 3, -2, 5, -8, 2, -2};
    int arr2[] = {6, 5, 4, -1, 3, 2, -1, 1};
    int arr3[] = {-5, -5, -5, -5, 7, -5};
    int arr4[] = {};
    int arr5[] = {1, -1, 2, -2, 3, -3};

    printArray(posNegSort(arr1, 7), 7);
    printArray(posNegSort(arr2, 8), 8);
    printArray(posNegSort(arr3, 6), 6);
    printArray(posNegSort(arr4, 0), 0);
    printArray(posNegSort(arr5, 6), 6);

    return 0;
}