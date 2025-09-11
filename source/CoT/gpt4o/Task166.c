#include <stdio.h>
#include <stdlib.h>

void posNegSort(int* arr, int size) {
    int* positives = (int*)malloc(size * sizeof(int));
    int posIndex = 0;
    
    for (int i = 0; i < size; ++i) {
        if (arr[i] > 0) {
            positives[posIndex++] = arr[i];
        }
    }
    
    qsort(positives, posIndex, sizeof(int), (int(*)(const void*, const void*))cmp);
    
    posIndex = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] > 0) {
            arr[i] = positives[posIndex++];
        }
    }
    free(positives);
}

int cmp(const int* a, const int* b) {
    return (*a > *b) - (*a < *b);
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int test1[] = {6, 3, -2, 5, -8, 2, -2};
    int test2[] = {6, 5, 4, -1, 3, 2, -1, 1};
    int test3[] = {-5, -5, -5, -5, 7, -5};
    int test4[] = {};
    int test5[] = {-10, 1, 2, -1, 0, 3};
    
    int* testCases[] = {test1, test2, test3, test4, test5};
    int sizes[] = {7, 8, 6, 0, 5};
    
    for (int i = 0; i < 5; ++i) {
        posNegSort(testCases[i], sizes[i]);
        printArray(testCases[i], sizes[i]);
    }
    return 0;
}