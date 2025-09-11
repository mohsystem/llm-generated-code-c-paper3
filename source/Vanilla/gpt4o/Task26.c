#include <stdio.h>

int findOddC(int array[], int length) {
    int result = 0;
    for (int i = 0; i < length; i++) {
        result ^= array[i];
    }
    return result;
}

int main() {
    int array1[] = {7};
    int array2[] = {0};
    int array3[] = {1, 1, 2};
    int array4[] = {0, 1, 0, 1, 0};
    int array5[] = {1, 2, 2, 3, 3, 3, 4, 3, 3, 3, 2, 2, 1};

    printf("%d\n", findOddC(array1, 1)); // 7
    printf("%d\n", findOddC(array2, 1)); // 0
    printf("%d\n", findOddC(array3, 3)); // 2
    printf("%d\n", findOddC(array4, 5)); // 0
    printf("%d\n", findOddC(array5, 13)); // 4

    return 0;
}