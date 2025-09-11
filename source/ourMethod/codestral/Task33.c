#include <stdio.h>
#include <stdlib.h>

int findMinIndex(int *array, int size) {
    int minIndex = 0;
    for (int i = 1; i < size; i++) {
        if (array[i] < array[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

int queueTime(int *customers, int size, int n) {
    int tills[n];
    for (int i = 0; i < n; i++) {
        tills[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        int minIndex = findMinIndex(tills, n);
        tills[minIndex] += customers[i];
    }
    int max = tills[0];
    for (int i = 1; i < n; i++) {
        if (tills[i] > max) {
            max = tills[i];
        }
    }
    return max;
}

int main() {
    int customers1[] = {5,3,4};
    printf("%d\n", queueTime(customers1, 3, 1)); // Output: 12
    int customers2[] = {10,2,3,3};
    printf("%d\n", queueTime(customers2, 4, 2)); // Output: 10
    int customers3[] = {2,3,10};
    printf("%d\n", queueTime(customers3, 3, 2)); // Output: 12
    return 0;
}