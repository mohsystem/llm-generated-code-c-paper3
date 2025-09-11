#include <stdio.h>

const char* oddOrEven(int array[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum % 2 == 0 ? "even" : "odd";
}

int main() {
    int array1[] = {0};
    int array2[] = {0, 1, 4};
    int array3[] = {0, -1, -5};
    printf("%s\n", oddOrEven(array1, 1)); // "even"
    printf("%s\n", oddOrEven(array2, 3)); // "odd"
    printf("%s\n", oddOrEven(array3, 3)); // "even"
    return 0;
}