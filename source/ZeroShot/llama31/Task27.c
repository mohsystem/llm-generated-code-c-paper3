#include <stdio.h>

int findOutlier(int arr[], int size) {
    int oddCount = 0;
    int evenCount = 0;
    int oddNum = 0;
    int evenNum = 0;

    for (int i = 0; i < 3; i++) {
        if (arr[i] % 2 == 0) {
            evenCount++;
            evenNum = arr[i];
        } else {
            oddCount++;
            oddNum = arr[i];
        }
    }

    return (evenCount > oddCount) ? oddNum : evenNum;
}

int main() {
    int test1[] = {2, 4, 0, 100, 4, 11, 2602, 36};
    int test2[] = {160, 3, 1719, 19, 11, 13, -21};
    int test3[] = {1, 3, 5, 7, 9, 10};
    int test4[] = {2, 4, 6, 8, 10, 11};
    int test5[] = {100, 200, 300, 400, 500, 501};

    printf("%d\n", findOutlier(test1, sizeof(test1)/sizeof(test1[0]))); // Output: 11
    printf("%d\n", findOutlier(test2, sizeof(test2)/sizeof(test2[0]))); // Output: 160
    printf("%d\n", findOutlier(test3, sizeof(test3)/sizeof(test3[0]))); // Output: 10
    printf("%d\n", findOutlier(test4, sizeof(test4)/sizeof(test4[0]))); // Output: 11
    printf("%d\n", findOutlier(test5, sizeof(test5)/sizeof(test5[0]))); // Output: 501

    return 0;
}