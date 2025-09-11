#include <stdio.h>

int findOutlier(const int* integers, int size) {
    int countEven = 0;
    int countOdd = 0;
    int lastEven = 0;
    int lastOdd = 0;

    for (int i = 0; i < size; i++) {
        if (integers[i] % 2 == 0) {
            countEven++;
            lastEven = integers[i];
        } else {
            countOdd++;
            lastOdd = integers[i];
        }
        if (countEven > 1 && countOdd > 0) {
            return lastOdd;
        }
        if (countOdd > 1 && countEven > 0) {
            return lastEven;
        }
    }
    return countEven > countOdd ? lastOdd : lastEven;
}

int main() {
    int testCases[][8] = {
        {2, 4, 0, 100, 4, 11, 2602, 36},
        {160, 3, 1719, 19, 11, 13, -21},
        {2, 6, 8, 10, 3},
        {1, 1, 1, 1, 2},
        {-102, -200, -301, -400}
    };
    int sizes[] = {8, 7, 5, 5, 4};

    for (int i = 0; i < 5; i++) {
        printf("%d\n", findOutlier(testCases[i], sizes[i]));
    }
    return 0;
}