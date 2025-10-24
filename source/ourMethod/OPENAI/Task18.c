#include <stdio.h>
#include <limits.h>
#include <stddef.h>

int binary_array_to_int(const int* bits, size_t len) {
    if (bits == NULL && len > 0) {
        return -1; /* invalid input pointer */
    }
    long long result = 0;
    for (size_t i = 0; i < len; ++i) {
        int bit = bits[i];
        if (bit != 0 && bit != 1) {
            return -1; /* invalid bit */
        }
        if (result > (LLONG_MAX / 2)) {
            return -1; /* internal overflow safeguard */
        }
        if (result > (INT_MAX - bit) / 2LL) {
            return -1; /* would overflow 32-bit int */
        }
        result = (result << 1) | bit;
    }
    return (int)result;
}

static void print_array(const int* arr, size_t len) {
    printf("[");
    for (size_t i = 0; i < len; ++i) {
        printf("%d", arr[i]);
        if (i + 1 < len) {
            printf(", ");
        }
    }
    printf("]");
}

int main(void) {
    int t1[] = {0, 0, 0, 1};
    int t2[] = {0, 0, 1, 0};
    int t3[] = {0, 1, 0, 1};
    int t4[] = {1, 0, 0, 1};
    int t5[] = {1, 1, 1, 1};

    const int* tests[] = {t1, t2, t3, t4, t5};
    size_t lens[] = {4, 4, 4, 4, 4};

    for (size_t i = 0; i < sizeof(tests)/sizeof(tests[0]); ++i) {
        int res = binary_array_to_int(tests[i], lens[i]);
        printf("Testing: ");
        print_array(tests[i], lens[i]);
        if (res >= 0) {
            printf(" ==> %d\n", res);
        } else {
            printf(" ==> Error: invalid input or overflow\n");
        }
    }
    return 0;
}