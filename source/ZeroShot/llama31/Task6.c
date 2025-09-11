#include <stdio.h>

double findUniq(double arr[], int n) {
    double first = arr[0];
    double second = arr[1];
    if (first != second) {
        if (first == arr[2]) {
            return second;
        } else {
            return first;
        }
    }
    for (int i = 2; i < n; i++) {
        if (arr[i] != first) {
            return arr[i];
        }
    }
    return first;  // This line should never be reached
}

int main() {
    double testCases[][6] = {
        {1, 1, 1, 2, 1, 1},
        {0, 0, 0.55, 0, 0},
        {3, 3, 3, 4, 3, 3},
        {5, 5, 5, 5, 6},
        {7, 7, 7, 8, 7}
    };
    int sizes[] = {6, 5, 6, 5, 5};
    for (int i = 0; i < 5; i++) {
        printf("Unique element: %f\n", findUniq(testCases[i], sizes[i]));
    }
    return 0;
}