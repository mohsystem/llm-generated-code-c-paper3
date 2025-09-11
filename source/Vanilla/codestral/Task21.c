#include <stdio.h>
#include <stdlib.h>

void removeSmallest(int* numbers, int length, int** result, int* resultLength) {
    if (length == 0) {
        *result = NULL;
        *resultLength = 0;
        return;
    }

    int minValue = numbers[0];
    for (int i = 1; i < length; i++) {
        if (numbers[i] < minValue) {
            minValue = numbers[i];
        }
    }

    int count = 0;
    for (int i = 0; i < length; i++) {
        if (numbers[i] != minValue || count > 0) {
            count++;
        }
    }

    *result = (int*)malloc(count * sizeof(int));
    *resultLength = count;

    int index = 0;
    for (int i = 0; i < length; i++) {
        if (numbers[i] != minValue || index > 0) {
            (*result)[index] = numbers[i];
            index++;
        }
    }
}

void printArray(int* arr, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int test1[] = {1, 2, 3, 4, 5};
    int* result1;
    int resultLength1;
    removeSmallest(test1, 5, &result1, &resultLength1);
    printArray(result1, resultLength1);  // 2 3 4 5
    free(result1);

    int test2[] = {5, 3, 2, 1, 4};
    int* result2;
    int resultLength2;
    removeSmallest(test2, 5, &result2, &resultLength2);
    printArray(result2, resultLength2);  // 5 3 2 4
    free(result2);

    int test3[] = {2, 2, 1, 2, 1};
    int* result3;
    int resultLength3;
    removeSmallest(test3, 5, &result3, &resultLength3);
    printArray(result3, resultLength3);  // 2 2 2 1
    free(result3);

    int test4[] = {};
    int* result4;
    int resultLength4;
    removeSmallest(test4, 0, &result4, &resultLength4);
    printArray(result4, resultLength4);  //
    free(result4);

    int test5[] = {1, 1, 1, 1, 1};
    int* result5;
    int resultLength5;
    removeSmallest(test5, 5, &result5, &resultLength5);
    printArray(result5, resultLength5);  // 1 1 1 1
    free(result5);

    return 0;
}