#include <stdio.h>

int findOdd(int arr[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= arr[i];
    }
    return result;
}

int main() {
    printf("%d\n", findOdd((int[]){7}, 1)); // 7
    printf("%d\n", findOdd((int[]){0}, 1)); // 0
    printf("%d\n", findOdd((int[]){1, 1, 2}, 3)); // 2
    printf("%d\n", findOdd((int[]){0, 1, 0, 1, 0}, 5)); // 0
    printf("%d\n", findOdd((int[]){1, 2, 2, 3, 3, 3, 4, 3, 3, 3, 2, 2, 1}, 13)); // 4
    return 0;
}