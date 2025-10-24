#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    int idx1;
    int idx2;
    int valid; /* 1 if valid result, 0 otherwise */
} Pair;

Pair two_sum(const long long* numbers, size_t length, long long target) {
    Pair result;
    result.idx1 = -1;
    result.idx2 = -1;
    result.valid = 0;

    if (numbers == NULL || length < 2) {
        return result; /* invalid input */
    }

    for (size_t i = 0; i + 1 < length; ++i) {
        for (size_t j = i + 1; j < length; ++j) {
            if (numbers[i] + numbers[j] == target) {
                result.idx1 = (int)i;
                result.idx2 = (int)j;
                result.valid = 1;
                return result;
            }
        }
    }
    return result; /* no solution found */
}

static void run_test(const long long* nums, size_t len, long long target) {
    Pair res = two_sum(nums, len, target);
    printf("Input: {");
    for (size_t i = 0; i < len; ++i) {
        printf("%lld", nums[i]);
        if (i + 1 < len) {
            printf(", ");
        }
    }
    printf("}, target=%lld -> ", target);
    if (res.valid) {
        printf("{%d, %d}\n", res.idx1, res.idx2);
    } else {
        printf("No valid pair found\n");
    }
}

int main(void) {
    long long a1[] = {1, 2, 3};
    long long a2[] = {3, 2, 4};
    long long a3[] = {3, 3};
    long long a4[] = {-1, -2, -3, -4, -5};
    long long a5[] = {0, 4, 3, 0};

    run_test(a1, sizeof(a1)/sizeof(a1[0]), 4);    /* expected {0,2} */
    run_test(a2, sizeof(a2)/sizeof(a2[0]), 6);    /* expected {1,2} */
    run_test(a3, sizeof(a3)/sizeof(a3[0]), 6);    /* expected {0,1} */
    run_test(a4, sizeof(a4)/sizeof(a4[0]), -8);   /* expected {2,4} */
    run_test(a5, sizeof(a5)/sizeof(a5[0]), 0);    /* expected {0,3} */

    return 0;
}