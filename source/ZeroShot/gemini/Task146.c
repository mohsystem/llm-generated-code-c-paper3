#include <stdio.h>
#include <stdlib.h>

int findMissingNumber(int arr[], int n) {
    int i, total;
    total = (n + 1) * (n + 2) / 2;
    for (i = 0; i < n; i++)
        total -= arr[i];
    return total;
}

int main() {
    int test1[] = {1, 2, 4, 5, 6};
    int test2[] = {1, 2, 3, 4, 6, 7, 8};
    int test3[] = {2, 3, 4, 5};
    int test4[] = {1, 3, 4, 5, 6};
    int test5[] = {1};

    printf("%d\n", findMissingNumber(test1, 5)); // Output: 3
    printf("%d\n", findMissingNumber(test2, 7)); // Output: 5
    printf("%d\n", findMissingNumber(test3, 4)); // Output: 1
    printf("%d\n", findMissingNumber(test4, 5)); // Output: 2
    printf("%d\n", findMissingNumber(test5, 1)); // Output: 2

    return 0;
}