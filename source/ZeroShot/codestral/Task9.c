#include <stdio.h>

const char* oddOrEven(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return (sum % 2 == 0) ? "even" : "odd";
}

int main() {
    int arr1[] = {0};
    int arr2[] = {0, 1, 4};
    int arr3[] = {0, -1, -5};
    printf("%s\n", oddOrEven(arr1, 1)); // "even"
    printf("%s\n", oddOrEven(arr2, 3)); // "odd"
    printf("%s\n", oddOrEven(arr3, 3)); // "even"
    return 0;
}