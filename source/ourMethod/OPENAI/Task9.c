#include <stdio.h>
#include <stddef.h>

const char* odd_or_even(const int* arr, size_t len) {
    if (arr == NULL || len == 0) {
        return "even";
    }
    int parity = 0;
    for (size_t i = 0; i < len; i++) {
        int r = arr[i] % 2;
        if (r < 0) r = -r;
        parity ^= r;
    }
    return (parity == 0) ? "even" : "odd";
}

int main(void) {
    const char* result;

    // Test 1: empty (len=0)
    result = odd_or_even(NULL, 0);
    printf("%s\n", result); // even

    // Test 2: [0]
    int a2[] = {0};
    printf("%s\n", odd_or_even(a2, sizeof(a2)/sizeof(a2[0]))); // even

    // Test 3: [0, 1, 4]
    int a3[] = {0, 1, 4};
    printf("%s\n", odd_or_even(a3, sizeof(a3)/sizeof(a3[0]))); // odd

    // Test 4: [0, -1, -5]
    int a4[] = {0, -1, -5};
    printf("%s\n", odd_or_even(a4, sizeof(a4)/sizeof(a4[0]))); // even

    // Test 5: [2, 3, 5, 7]
    int a5[] = {2, 3, 5, 7};
    printf("%s\n", odd_or_even(a5, sizeof(a5)/sizeof(a5[0]))); // odd

    return 0;
}