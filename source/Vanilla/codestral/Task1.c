#include<stdio.h>

int number(int arr[][2], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += arr[i][0] - arr[i][1];
    }
    return total;
}

int main() {
    int test1[][2] = {{10, 0}, {3, 5}, {5, 8}};
    int test2[][2] = {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}};
    int test3[][2] = {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}};
    int test4[][2] = {{0, 0}};
    int test5[][2] = {{10, 0}, {2, 5}, {3, 4}};

    printf("%d\n", number(test1, 3)); // Expected output: 5
    printf("%d\n", number(test2, 6)); // Expected output: 17
    printf("%d\n", number(test3, 6)); // Expected output: 9
    printf("%d\n", number(test4, 1)); // Expected output: 0
    printf("%d\n", number(test5, 3)); // Expected output: 4

    return 0;
}