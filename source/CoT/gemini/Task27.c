#include <stdio.h>

int findOutlier(int arr[], int size) {
    int evenCount = 0;
    int oddCount = 0;

    for (int i = 0; i < 3; i++) {
        if (arr[i] % 2 == 0) {
            evenCount++;
        } else {
            oddCount++;
        }
    }

    int isEvenOutlier = oddCount > evenCount;

    for (int i = 0; i < size; i++) {
        if (isEvenOutlier) {
            if (arr[i] % 2 == 0) {
                return arr[i];
            }
        } else {
            if (arr[i] % 2 != 0) {
                return arr[i];
            }
        }
    }

    return -1; // Should not reach here as per problem statement
}

int main() {
    int test1[] = {2, 4, 0, 100, 4, 11, 2602, 36};
    int test2[] = {160, 3, 1719, 19, 11, 13, -21};
    int test3[] = {1, 3, 5, 7, 9, 2};
    int test4[] = {2, 4, 6, 8, 1};
    int test5[] = {2, 4, 6, 8, 0};


    printf("%d\n", findOutlier(test1, 8)); //11
    printf("%d\n", findOutlier(test2, 7)); //160
    printf("%d\n", findOutlier(test3, 6)); //2
    printf("%d\n", findOutlier(test4, 5)); //1
    printf("%d\n", findOutlier(test5, 5)); //0

    return 0;
}