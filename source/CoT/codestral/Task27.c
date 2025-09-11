#include <stdio.h>

int findOutlier(int arr[], int size) {
    int countEven = 0, countOdd = 0, even = 0, odd = 0;

    for (int i = 0; i < 3; i++) {
        if (arr[i] % 2 == 0) {
            countEven++;
            even = arr[i];
        } else {
            countOdd++;
            odd = arr[i];
        }
    }

    for (int i = 3; i < size; i++) {
        if (arr[i] % 2 == 0) {
            countEven++;
            even = arr[i];
        } else {
            countOdd++;
            odd = arr[i];
        }

        if (countEven > 1 && countOdd == 1) {
            return odd;
        } else if (countOdd > 1 && countEven == 1) {
            return even;
        }
    }

    return countEven > countOdd ? odd : even;
}

int main() {
    int arr1[] = {2, 4, 0, 100, 4, 11, 2602, 36};
    int arr2[] = {160, 3, 1719, 19, 11, 13, -21};

    printf("%d\n", findOutlier(arr1, sizeof(arr1) / sizeof(arr1[0])));
    printf("%d\n", findOutlier(arr2, sizeof(arr2) / sizeof(arr2[0])));

    return 0;
}