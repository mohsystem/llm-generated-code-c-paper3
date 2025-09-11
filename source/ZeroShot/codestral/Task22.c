#include <stdio.h>
#include <stdlib.h>

void filterList(int* arr, int n, int** result, int* result_size) {
    *result = (int*)malloc(sizeof(int) * n);
    *result_size = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] != -1) {  // assuming -1 as invalid value
            (*result)[(*result_size)++] = arr[i];
        }
    }
}

int main() {
    int* result;
    int result_size;
    int arr[] = {1, 2, -1, -1};
    filterList(arr, 4, &result, &result_size);
    for (int i = 0; i < result_size; i++) {
        printf("%d ", result[i]);
    }
    free(result);
    return 0;
}