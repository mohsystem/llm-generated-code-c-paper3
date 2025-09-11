#include <stdio.h>
#include <stdlib.h>

void sortArray(int* array, int size) {
    if (array == NULL || size <= 0) {
        printf("Input array cannot be null or empty");
        exit(1);
    }
    qsort(array, size, sizeof(int), compare);
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int array[] = {5, 2, 8, 3, 1};
    int size = sizeof(array) / sizeof(array[0]);
    sortArray(array, size);
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    return 0;
}