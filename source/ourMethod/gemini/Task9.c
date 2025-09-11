#include <stdio.h>
#include <string.h>

char* oddOrEven(int array[], int size) {
    if (size == 0) {
        return "even";
    }
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return (sum % 2 == 0) ? "even" : "odd";
}

int main() {
    int test1[] = {0};
    printf("Test 1: %s\n", oddOrEven(test1, 1)); // Output: even

    int test2[] = {0, 1, 4};
    printf("Test 2: %s\n", oddOrEven(test2, 3)); // Output: odd

    int test3[] = {0, -1, -5};
    printf("Test 3: %s\n", oddOrEven(test3, 3)); // Output: even

    int test4[] = {};
    printf("Test 4: %s\n", oddOrEven(test4, 0)); // Output: even

    int test5[] = {1, 2, 3, 4, 5};
    printf("Test 5: %s\n", oddOrEven(test5, 5)); // Output: odd

    return 0;
}