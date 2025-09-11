#include <stdio.h>

int longestRun(int* numbers, int length) {
    if (numbers == NULL || length == 0) return 0;

    int maxRun = 1;
    int currentRun = 1;

    for (int i = 1; i < length; i++) {
        if (numbers[i] == numbers[i - 1] + 1 || numbers[i] == numbers[i - 1] - 1) {
            currentRun++;
        } else {
            currentRun = 1;
        }
        if (currentRun > maxRun) {
            maxRun = currentRun;
        }
    }

    return maxRun;
}

int main() {
    int arr1[] = {1, 2, 3, 10, 11, 15};
    int arr2[] = {5, 4, 2, 1};
    int arr3[] = {3, 5, 7, 10, 15};
    int arr4[] = {1, 2, 3, 5, 6, 7, 8, 9};
    int arr5[] = {9, 8, 7, 6, 5, 4, 3};

    printf("%d\n", longestRun(arr1, 6)); // 3
    printf("%d\n", longestRun(arr2, 4)); // 2
    printf("%d\n", longestRun(arr3, 5)); // 1
    printf("%d\n", longestRun(arr4, 8)); // 5
    printf("%d\n", longestRun(arr5, 7)); // 7

    return 0;
}