#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

const char* oddOrEven(int arr[], int size) {
    if (arr == NULL) {
        return "even";
    }
    int sum = 0;
    for (int i = 0; i < size; i++) {
        // Prevent Integer Overflow or Wraparound
        if (INT_MAX - sum < arr[i]) {
            printf("Sum is too large\n");
            exit(EXIT_FAILURE);
        }
        sum += arr[i];
    }
    return (sum % 2 == 0) ? "even" : "odd";
}

int main() {
    int arr1[] = {0};
    int arr2[] = {0, 1, 4};
    int arr3[] = {0, -1, -5};
    printf("%s\n", oddOrEven(arr1, 1)); // even
    printf("%s\n", oddOrEven(arr2, 3)); // odd
    printf("%s\n", oddOrEven(arr3, 3)); // even
    return 0;
}