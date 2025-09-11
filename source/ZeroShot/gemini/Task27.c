#include <stdio.h>

int findOutlier(int arr[], int len) {
    int evenCount = 0;
    for (int i = 0; i < 3; i++) {
        if (arr[i] % 2 == 0) {
            evenCount++;
        }
    }

    int isEvenOutlier = evenCount < 2;

    for (int i = 0; i < len; i++) {
        if (isEvenOutlier) {
            if (arr[i] % 2 != 0) {
                return arr[i];
            }
        } else {
            if (arr[i] % 2 == 0) {
                return arr[i];
            }
        }
    }
    return 0; // Should never reach here
}

int main() {
    int test1[] = {2, 4, 0, 100, 4, 11, 2602, 36};
    int test2[] = {160, 3, 1719, 19, 11, 13, -21};
    int test3[] = {1, 1, 2};
    int test4[] = {2, 4, 6};
    int test5[] = {1, 3, 5, 2};

    printf("%d\n", findOutlier(test1, 8)); // 11
    printf("%d\n", findOutlier(test2, 7)); // 160
    printf("%d\n", findOutlier(test3, 3)); // 2
    printf("%d\n", findOutlier(test4, 3)); // 0
    printf("%d\n", findOutlier(test5, 4)); // 2
    return 0;
}