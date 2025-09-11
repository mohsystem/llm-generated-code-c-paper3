#include <stdio.h>
#include <stdlib.h>

int* removeSmallest(int* numbers, int length, int* newLength) {
    if (length == 0) {
        *newLength = 0;
        return NULL;
    }
    int min = numbers[0];
    int index = 0;
    for (int i = 1; i < length; i++) {
        if (numbers[i] < min) {
            min = numbers[i];
            index = i;
        }
    }
    int* result = malloc(sizeof(int) * (length - 1));
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (i != index) {
            result[j++] = numbers[i];
        }
    }
    *newLength = length - 1;
    return result;
}

int main() {
    int newLength;
    int* result = removeSmallest((int[]){1,2,3,4,5}, 5, &newLength);
    for (int i = 0; i < newLength; i++) printf("%d ", result[i]); // Output: 2 3 4 5
    printf("\n");
    free(result);
    result = removeSmallest((int[]){5,3,2,1,4}, 5, &newLength);
    for (int i = 0; i < newLength; i++) printf("%d ", result[i]); // Output: 5 3 2 4
    printf("\n");
    free(result);
    result = removeSmallest((int[]){2,2,1,2,1}, 5, &newLength);
    for (int i = 0; i < newLength; i++) printf("%d ", result[i]); // Output: 2 2 2 1
    free(result);
    return 0;
}