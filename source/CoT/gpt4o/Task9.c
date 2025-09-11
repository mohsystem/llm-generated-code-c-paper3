#include <stdio.h>

const char* oddOrEven(int numbers[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += numbers[i];
    }
    return (sum % 2 == 0) ? "even" : "odd";
}

int main() {
    int numbers1[] = {0};
    int numbers2[] = {0, 1, 4};
    int numbers3[] = {0, -1, -5};
    int numbers4[] = {2, 2, 2};
    int numbers5[] = {1, 1, 1};

    printf("%s\n", oddOrEven(numbers1, 1)); // even
    printf("%s\n", oddOrEven(numbers2, 3)); // odd
    printf("%s\n", oddOrEven(numbers3, 3)); // even
    printf("%s\n", oddOrEven(numbers4, 3)); // even
    printf("%s\n", oddOrEven(numbers5, 3)); // odd

    return 0;
}