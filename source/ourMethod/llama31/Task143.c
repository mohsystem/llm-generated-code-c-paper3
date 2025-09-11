#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(int array[], int size) {
    for (int step = 0; step < size - 1; step++) {
        int min_idx = step;
        for (int i = step + 1; i < size; i++) {
            if (array[i] < array[min_idx]) {
                min_idx = i;
            }
        }
        // Swap the found minimum element with the first element of the unsorted part
        swap(&array[step], &array[min_idx]);
    }
}

void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int data1[] = {20, 12, 10, 15, 2};
    int data2[] = {64, 34, 25, 12, 22, 11, 90};
    int data3[] = {-2, 45, 0, 11, -9};
    int data4[] = {1, 1, 1, 1, 1};
    int data5[] = {5, 4, 3, 2, 1};

    int size1 = sizeof(data1) / sizeof(data1[0]);
    int size2 = sizeof(data2) / sizeof(data2[0]);
    int size3 = sizeof(data3) / sizeof(data3[0]);
    int size4 = sizeof(data4) / sizeof(data4[0]);
    int size5 = sizeof(data5) / sizeof(data5[0]);

    selectionSort(data1, size1);
    printf("Sorted Array 1: \n");
    printArray(data1, size1);

    selectionSort(data2, size2);
    printf("Sorted Array 2: \n");
    printArray(data2, size2);

    selectionSort(data3, size3);
    printf("Sorted Array 3: \n");
    printArray(data3, size3);

    selectionSort(data4, size4);
    printf("Sorted Array 4: \n");
    printArray(data4, size4);

    selectionSort(data5, size5);
    printf("Sorted Array 5: \n");
    printArray(data5, size5);

    return 0;
}