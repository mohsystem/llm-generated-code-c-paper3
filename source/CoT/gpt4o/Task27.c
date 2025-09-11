#include <stdio.h>

int findOutlier(int array[], int length) {
    int evenCount = 0;
    int oddCount = 0;
    int lastEven = 0;
    int lastOdd = 0;

    for (int i = 0; i < length; i++) {
        if (array[i] % 2 == 0) {
            evenCount++;
            lastEven = array[i];
        } else {
            oddCount++;
            lastOdd = array[i];
        }
        if (evenCount > 1 && oddCount > 0) {
            return lastOdd;
        }
        if (oddCount > 1 && evenCount > 0) {
            return lastEven;
        }
    }
    return 0; // should never reach here if input is valid
}

int main() {
    int array1[] = {2, 4, 0, 100, 4, 11, 2602, 36};
    int array2[] = {160, 3, 1719, 19, 11, 13, -21};
    int array3[] = {2, 6, 8, 10, 3};
    int array4[] = {1, 3, 5, 7, 4};
    int array5[] = {-2, -4, 5, -8};

    printf("%d\n", findOutlier(array1, sizeof(array1)/sizeof(array1[0]))); // 11
    printf("%d\n", findOutlier(array2, sizeof(array2)/sizeof(array2[0]))); // 160
    printf("%d\n", findOutlier(array3, sizeof(array3)/sizeof(array3[0]))); // 3
    printf("%d\n", findOutlier(array4, sizeof(array4)/sizeof(array4[0]))); // 4
    printf("%d\n", findOutlier(array5, sizeof(array5)/sizeof(array5[0]))); // 5

    return 0;
}