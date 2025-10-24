#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

static bool mul_overflow_ull(unsigned long long a, unsigned long long b, unsigned long long *res) {
    if (a == 0ULL || b == 0ULL) { *res = 0ULL; return false; }
    if (a > ULLONG_MAX / b) return true;
    *res = a * b;
    return false;
}

static bool add_overflow_ull(unsigned long long a, unsigned long long b, unsigned long long *res) {
    if (ULLONG_MAX - a < b) return true;
    *res = a + b;
    return false;
}

static unsigned long long int_pow_ull(unsigned int base, unsigned int exp, bool *overflow) {
    *overflow = false;
    unsigned long long result = 1ULL;
    for (unsigned int i = 0; i < exp; ++i) {
        unsigned long long tmp = 0ULL;
        if (mul_overflow_ull(result, (unsigned long long)base, &tmp)) { *overflow = true; return 0ULL; }
        result = tmp;
    }
    return result;
}

bool is_narcissistic(unsigned long long n) {
    if (n == 0ULL) return false;
    unsigned int power = 0U;
    unsigned long long t = n;
    while (t > 0ULL) { ++power; t /= 10ULL; }

    unsigned long long sum = 0ULL;
    t = n;
    while (t > 0ULL) {
        unsigned int digit = (unsigned int)(t % 10ULL);
        bool of = false;
        unsigned long long term = int_pow_ull(digit, power, &of);
        if (of) return false;
        unsigned long long newSum = 0ULL;
        if (add_overflow_ull(sum, term, &newSum)) return false;
        sum = newSum;
        t /= 10ULL;
    }
    return sum == n;
}

static const char* b2s(bool b) { return b ? "true" : "false"; }

int main(void) {
    unsigned long long tests[5] = {1ULL, 153ULL, 370ULL, 1652ULL, 9474ULL};
    for (int i = 0; i < 5; ++i) {
        printf("n=%llu -> %s\n", tests[i], b2s(is_narcissistic(tests[i])));
    }
    return 0;
}