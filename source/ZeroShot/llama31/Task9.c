#include <stdio.h>

char* isSumOddOrEven(int arr[], int size) {
    static char result[6];
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    if (sum % 2 == 0) {
        strcpy(result, "even");
    } else {
        strcpy(result, "odd");
    }
    return result;
}

int main() {
    int testCases[][6] = {
        {0},
        {0, 1, 4},
        {0, -1, -5},
        {1, 3, 5},
        {-2, -4, -6}
    };
    int sizes[] = {1, 3, 3, 3, 3};
    for (int i = 0; i < 5; ++i) {
        printf("%s\n", isSumOddOrEven(testCases[i], sizes[i]));
    }
    return 0;
}