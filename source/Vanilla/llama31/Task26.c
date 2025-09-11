#include <stdio.h>

int findOddOccurrence(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count % 2 != 0) {
            return arr[i];
        }
    }
    return -1; // This line should not be reached based on the problem statement
}

int main() {
    int testCases[][12] = {
        {7},
        {0},
        {1, 1, 2},
        {0, 1, 0, 1, 0},
        {1, 2, 2, 3, 3, 3, 4, 3, 3, 3, 2, 2, 1}
    };
    int sizes[] = {1, 1, 3, 5, 12};

    for (int i = 0; i < 5; i++) {
        printf("%d\n", findOddOccurrence(testCases[i], sizes[i]));
    }

    return 0;
}