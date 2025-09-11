#include <stdio.h>
#include <limits.h>

int findMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int findMinIndex(int arr[], int size) {
    int minIndex = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

int queueTime(int customers[], int n, int size) {
    if (n >= size) {
        return findMax(customers, size);
    }
    int tills[n];
    for (int i = 0; i < n; i++) {
        tills[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        int minIndex = findMinIndex(tills, n);
        tills[minIndex] += customers[i];
    }
    return findMax(tills, n);
}

int main() {
    // Test cases
    int customers1[] = {5, 3, 4};
    int customers2[] = {10, 2, 3, 3};
    int customers3[] = {2, 3, 10};
    printf("%d\n", queueTime(customers1, 1, 3)); // Should return 12
    printf("%d\n", queueTime(customers2, 2, 4)); // Should return 10
    printf("%d\n", queueTime(customers3, 2, 3)); // Should return 12
    return 0;
}