#include <stdio.h>

const char* sumOddOrEven(int* numbers, int length) {
    if (numbers == NULL || length == 0) {
        return "even";
    }
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += numbers[i];
    }
    return (sum % 2 == 0) ? "even" : "odd";
}

int main() {
    int arr1[] = {0};
    int arr2[] = {0, 1, 4};
    int arr3[] = {0, -1, -5};
    int arr4[] = {2, 3, 5};
    int arr5[] = {1, 1, 1, 1};

    printf("%s\n", sumOddOrEven(arr1, 1)); // "even"
    printf("%s\n", sumOddOrEven(arr2, 3)); // "odd"
    printf("%s\n", sumOddOrEven(arr3, 3)); // "even"
    printf("%s\n", sumOddOrEven(arr4, 3)); // "even"
    printf("%s\n", sumOddOrEven(arr5, 4)); // "even"

    return 0;
}