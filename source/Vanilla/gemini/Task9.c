#include <stdio.h>
#include <stdlib.h>

char* oddOrEven(int* array, int size) {
    int sum = 0;
    if (size == 0) {
        sum = 0;
    } else {
        for (int i = 0; i < size; i++) {
            sum += array[i];
        }
    }
    return (sum % 2 == 0) ? "even" : "odd";
}


int main() {
    int arr1[] = {0};
    printf("%s\n", oddOrEven(arr1, 1)); // Output: even

    int arr2[] = {0, 1, 4};
    printf("%s\n", oddOrEven(arr2, 3)); // Output: odd

    int arr3[] = {0, -1, -5};
    printf("%s\n", oddOrEven(arr3, 3)); // Output: even

    int arr4[] = {};
    printf("%s\n", oddOrEven(arr4, 0)); // Output: even
    printf("%s\n", oddOrEven(arr4, 0)); // Output: even

    return 0;
}