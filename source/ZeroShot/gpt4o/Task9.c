#include <stdio.h>

const char* oddOrEven(int numbers[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += numbers[i];
    }
    return sum % 2 == 0 ? "even" : "odd";
}

int main() {
    int arr1[] = {0};
    int arr2[] = {0, 1, 4};
    int arr3[] = {0, -1, -5};
    int arr4[] = {1, 3, 5};
    int arr5[] = {2, 4, 6};

    printf("%s\n", oddOrEven(arr1, 1));  // Output: "even"
    printf("%s\n", oddOrEven(arr2, 3));  // Output: "odd"
    printf("%s\n", oddOrEven(arr3, 3));  // Output: "even"
    printf("%s\n", oddOrEven(arr4, 3));  // Output: "odd"
    printf("%s\n", oddOrEven(arr5, 3));  // Output: "even"

    return 0;
}