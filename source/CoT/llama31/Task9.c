#include <stdio.h>

char* isSumOddOrEven(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    // If array is empty, consider sum as 0
    if (size == 0) {
        sum = 0;
    }
    return sum % 2 == 0 ? "even" : "odd";
}

int main() {
    int testCases[][5] = {
        {0},
        {0, 1, 4},
        {0, -1, -5},
        {},
        {1, 3, 5}
    };
    int sizes[] = {1, 3, 3, 0, 3};
    for (int i = 0; i < 5; i++) {
        printf("Input: ");
        for (int j = 0; j < sizes[i]; j++) {
            printf("%d ", testCases[i][j]);
        }
        if (sizes[i] == 0) {
            printf("0");
        }
        printf("\nOutput: %s\n\n", isSumOddOrEven(testCases[i], sizes[i]));
    }
    return 0;
}