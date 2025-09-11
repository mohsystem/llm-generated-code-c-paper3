#include <stdio.h>

char* isSumOddOrEven(int arr[], int n) {
    static char result[6];
    int sum = 0;
    for (int i = 0; i < n; i++) {
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
    int testCases[][5] = {
        {0},
        {0, 1, 4},
        {0, -1, -5},
        {}, // Empty array
        {2, 4, 6}
    };
    int lengths[] = {1, 3, 3, 0, 3};

    for (int i = 0; i < 5; i++) {
        if (lengths[i] == 0) {
            printf("even\n"); // Handle empty array case
        } else {
            printf("%s\n", isSumOddOrEven(testCases[i], lengths[i]));
        }
    }

    return 0;
}