#include <stdio.h>

char* isSumOddOrEven(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return sum % 2 == 0 ? "even" : "odd";
}

int main() {
    int testCases[][5] = {
        {0},
        {0, 1, 4},
        {0, -1, -5},
        {}, // Empty array
        {1, 3, 5}
    };

    int lengths[] = {1, 3, 3, 0, 3};

    for (int i = 0; i < 5; ++i) {
        printf("%s\n", isSumOddOrEven(testCases[i], lengths[i]));
    }

    return 0;
}