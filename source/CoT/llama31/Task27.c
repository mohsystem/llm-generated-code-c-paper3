#include <stdio.h>

int findOutlier(int arr[], int size) {
    int evenCount = 0;
    int oddCount = 0;
    int evenNum = 0;
    int oddNum = 0;

    for (int i = 0; i < 3; i++) {
        if (arr[i] % 2 == 0) {
            evenCount++;
            evenNum = arr[i];
        } else {
            oddCount++;
            oddNum = arr[i];
        }
    }

    if (evenCount > oddCount) {
        return oddNum;
    } else {
        return evenNum;
    }
}

int main() {
    int test1[] = {2, 4, 0, 100, 4, 11, 2602, 36};
    int test2[] = {160, 3, 1719, 19, 11, 13, -21};
    int test3[] = {1, 3, 5, 7, 9, 10};
    int test4[] = {2, 4, 6, 8, 10, 11};
    int test5[] = {100, 200, 300, 400, 500, 501};

    printf("%d\n", findOutlier(test1, 8)); // 11
    printf("%d\n", findOutlier(test2, 7)); // 160
    printf("%d\n", findOutlier(test3, 6)); // 10
    printf("%d\n", findOutlier(test4, 6)); // 11
    printf("%d\n", findOutlier(test5, 6)); // 501

    return 0;
}