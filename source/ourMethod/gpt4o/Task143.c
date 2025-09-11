#include <stdio.h>
#include <stdlib.h>

void sortArray(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int test1[] = {3, 1, 4, 1, 5, 9};
    int size1 = sizeof(test1) / sizeof(test1[0]);
    sortArray(test1, size1);
    printArray(test1, size1);

    int test2[] = {2, 7, 1, 8, 2, 8};
    int size2 = sizeof(test2) / sizeof(test2[0]);
    sortArray(test2, size2);
    printArray(test2, size2);

    int test3[] = {5, 0, 3, 9, 8, 9};
    int size3 = sizeof(test3) / sizeof(test3[0]);
    sortArray(test3, size3);
    printArray(test3, size3);

    int test4[] = {1, 1, 2, 3, 5, 8};
    int size4 = sizeof(test4) / sizeof(test4[0]);
    sortArray(test4, size4);
    printArray(test4, size4);

    int test5[] = {9, 7, 4, 6, 5, 3};
    int size5 = sizeof(test5) / sizeof(test5[0]);
    sortArray(test5, size5);
    printArray(test5, size5);

    return 0;
}