#include <stdio.h>
#include <string.h>

typedef struct {
    int success; /* 1 for success, 0 for failure */
    unsigned long long value;
    char error[64];
} FactorialResult;

static FactorialResult factorial(long long n) {
    FactorialResult res;
    res.success = 0;
    res.value = 0ULL;
    res.error[0] = '\0';

    if (n < 0) {
        snprintf(res.error, sizeof(res.error), "%s", "Input must be a non-negative integer.");
        return res;
    }
    /* Using 64-bit unsigned long long; 20! fits, 21! overflows */
    if (n > 20) {
        snprintf(res.error, sizeof(res.error), "%s", "Input too large; maximum supported is 20 for 64-bit.");
        return res;
    }
    unsigned long long acc = 1ULL;
    for (long long i = 2; i <= n; ++i) {
        acc *= (unsigned long long)i;
    }
    res.success = 1;
    res.value = acc;
    return res;
}

int main(void) {
    long long tests[5] = {0, 1, 5, 20, 21};
    for (int i = 0; i < 5; ++i) {
        long long n = tests[i];
        FactorialResult res = factorial(n);
        if (res.success) {
            printf("factorial(%lld) = %llu\n", n, (unsigned long long)res.value);
        } else {
            printf("factorial(%lld) error: %s\n", n, res.error);
        }
    }
    return 0;
}