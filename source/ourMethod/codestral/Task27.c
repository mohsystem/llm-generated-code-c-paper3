#include <stdio.h>

int findOutlier(int numbers[], int length) {
    int oddCount = 0;
    int evenCount = 0;
    int lastOdd = 0;
    int lastEven = 0;

    for (int i = 0; i < length; i++) {
        int number = numbers[i];
        if (number % 2 == 0) {
            evenCount++;
            lastEven = number;
        } else {
            oddCount++;
            lastOdd = number;
        }

        if (oddCount > 1 && evenCount == 1) {
            return lastEven;
        } else if (evenCount > 1 && oddCount == 1) {
            return lastOdd;
        }
    }

    return 0;
}

int main() {
    int numbers1[] = {2, 4, 0, 100, 4, 11, 2602, 36};
    int numbers2[] = {160, 3, 1719, 19, 11, 13, -21};

    printf("%d\n", findOutlier(numbers1, sizeof(numbers1) / sizeof(numbers1[0])));  // Output: 11
    printf("%d\n", findOutlier(numbers2, sizeof(numbers2) / sizeof(numbers2[0])));  // Output: 160

    return 0;
}