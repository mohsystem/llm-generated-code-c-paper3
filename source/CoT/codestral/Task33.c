#include <stdio.h>
#include <stdlib.h>

int minIndex(int* arr, int n) {
    int min = arr[0];
    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
            minIndex = i;
        }
    }
    return minIndex;
}

int maxValue(int* arr, int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int queueTime(int* customers, int n, int size) {
    int* tills = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < size; i++) {
        int minIndex = minIndex(tills, n);
        tills[minIndex] += customers[i];
    }
    int maxTime = maxValue(tills, n);
    free(tills);
    return maxTime;
}

int main() {
    int customers1[] = {5, 3, 4};
    int customers2[] = {10, 2, 3, 3};
    int customers3[] = {2, 3, 10};
    printf("%d\n", queueTime(customers1, 1, 3)); // should return 12
    printf("%d\n", queueTime(customers2, 2, 4)); // should return 10
    printf("%d\n", queueTime(customers3, 2, 3)); // should return 12
    return 0;
}