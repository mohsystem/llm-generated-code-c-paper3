#include <stdio.h>
#include <stdlib.h>

int queueTime(const int *customers, int size, int n) {
    if (n <= 0 || size <= 0) return 0;
    int *tills = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < size; ++i) {
        int minIndex = 0;
        for (int j = 1; j < n; ++j) {
            if (tills[j] < tills[minIndex]) {
                minIndex = j;
            }
        }
        tills[minIndex] += customers[i];
    }
    int maxTime = 0;
    for (int i = 0; i < n; ++i) {
        if (tills[i] > maxTime) {
            maxTime = tills[i];
        }
    }
    free(tills);
    return maxTime;
}

int main() {
    printf("%d\n", queueTime((int[]){5, 3, 4}, 3, 1)); // 12
    printf("%d\n", queueTime((int[]){10, 2, 3, 3}, 4, 2)); // 10
    printf("%d\n", queueTime((int[]){2, 3, 10}, 3, 2)); // 12
    printf("%d\n", queueTime((int[]){}, 0, 1)); // 0
    printf("%d\n", queueTime((int[]){1, 2, 3, 4, 5}, 5, 100)); // 5
    return 0;
}