#include <stdio.h>
#include <stdlib.h>

// Assuming input is an array of integers and strings, this solution doesn't directly support mixed types in C.
// We need to modify the input type to fit this approach.

int* filterList(int* arr, int size, int* newSize) {
    int* result = malloc(size * sizeof(int));
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] >= 0) { // Assuming non-negative integers and negative values for strings.
            result[count] = arr[i];
            count++;
        }
    }
    *newSize = count;
    return result;
}

int main() {
    int size;
    int* arr = filterList((int[]){1, 2, -1, -2}, 4, &size);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    free(arr);
    return 0;
}