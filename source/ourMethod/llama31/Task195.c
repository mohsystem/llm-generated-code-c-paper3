#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50000

int arr[MAX_SIZE];
int size = 0;

void addNum(int num) {
    arr[size++] = num;
    // Simple insertion sort for demonstration purposes
    for (int i = size - 1; i > 0; i--) {
        if (arr[i] < arr[i - 1]) {
            int temp = arr[i];
            arr[i] = arr[i - 1];
            arr[i - 1] = temp;
        } else {
            break;
        }
    }
}

double findMedian() {
    if (size % 2 == 0) {
        return (arr[size / 2 - 1] + arr[size / 2]) / 2.0;
    } else {
        return (double) arr[size / 2];
    }
}

int main() {
    addNum(1);
    addNum(2);
    printf("%f\n", findMedian()); // Output: 1.5
    addNum(3);
    printf("%f\n", findMedian()); // Output: 2.0
    return 0;
}