#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int find_odd(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        /* Invalid input; fail closed by returning 0 (ambiguous if 0 is valid). */
        return 0;
    }
    int result = 0;
    for (size_t i = 0; i < n; ++i) {
        result ^= arr[i];
    }
    return result;
}

int main(void) {
    int t1[] = {7};
    int t2[] = {0};
    int t3[] = {1, 1, 2};
    int t4[] = {0, 1, 0, 1, 0};
    int t5[] = {1, 2, 2, 3, 3, 3, 4, 3, 3, 3, 2, 2, 1};

    int r1 = find_odd(t1, sizeof(t1) / sizeof(t1[0]));
    int r2 = find_odd(t2, sizeof(t2) / sizeof(t2[0]));
    int r3 = find_odd(t3, sizeof(t3) / sizeof(t3[0]));
    int r4 = find_odd(t4, sizeof(t4) / sizeof(t4[0]));
    int r5 = find_odd(t5, sizeof(t5) / sizeof(t5[0]));

    printf("Test 1 result=%d\n", r1);
    printf("Test 2 result=%d\n", r2);
    printf("Test 3 result=%d\n", r3);
    printf("Test 4 result=%d\n", r4);
    printf("Test 5 result=%d\n", r5);

    return 0;
}