#include <stdio.h>

int number(int arr[][2], int size) {
    int numPeople = 0;
    for (int i = 0; i < size; i++) {
        numPeople += arr[i][0] - arr[i][1];
    }
    return numPeople;
}

int main() {
    int test1[][2] = {{10, 0}, {3, 5}, {5, 8}};
    int test2[][2] = {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}};
    int test3[][2] = {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}};
    int test4[][2] = {{0, 0}};
    int test5[][2] = {{2, 2}};

    printf("%d\n", number(test1, sizeof(test1) / sizeof(test1[0])));
    printf("%d\n", number(test2, sizeof(test2) / sizeof(test2[0])));
    printf("%d\n", number(test3, sizeof(test3) / sizeof(test3[0])));
    printf("%d\n", number(test4, sizeof(test4) / sizeof(test4[0])));
    printf("%d\n", number(test5, sizeof(test5) / sizeof(test5[0])));

    return 0;
}