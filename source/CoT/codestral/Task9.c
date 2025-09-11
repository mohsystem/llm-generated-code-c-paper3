#include <stdio.h>

const char* determine_parity(int arr[], int n) {
    if (n == 0) {
        return "even";
    }
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum % 2 == 0 ? "even" : "odd";
}

int main() {
    int arr1[] = {0};
    printf("%s\n", determine_parity(arr1, 1));  // Output: "even"

    int arr2[] = {0, 1, 4};
    printf("%s\n", determine_parity(arr2, 3));  // Output: "odd"

    int arr3[] = {0, -1, -5};
    printf("%s\n", determine_parity(arr3, 3));  // Output: "even"

    int arr4[0];
    printf("%s\n", determine_parity(arr4, 0));  // Output: "even"

    int arr5[] = {1, 2, 3, 4};
    printf("%s\n", determine_parity(arr5, 4));  // Output: "even"

    return 0;
}